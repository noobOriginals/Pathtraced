#include <metal_stdlib>
using namespace metal;

// ---------------------------------------------------------------------------
// GPU-side copies of GPUObject / GPURenderParams (must match gpu_scene.hpp)
// ---------------------------------------------------------------------------

struct GPUObject {
    int   type;
    float d[12];
    int   matType;
    float cr, cg, cb;
    float param;
};

struct GPURenderParams {
    int   width, height;
    int   samplesPerPixel, maxBounces;
    float camPosX, camPosY, camPosZ;
    float originX, originY, originZ;
    float deltaWX, deltaWY, deltaWZ;
    float deltaHX, deltaHY, deltaHZ;
    int   objectCount;
    int   pad;
};

// ---------------------------------------------------------------------------
// PRNG — xorshift32, seeded per pixel × sample
// ---------------------------------------------------------------------------

static uint xorshift32(thread uint& s) {
    s ^= s << 13;
    s ^= s >> 17;
    s ^= s << 5;
    return s;
}

static float rng(thread uint& s) {
    return float(xorshift32(s)) * (1.0f / 4294967296.0f);
}

// Random point on unit sphere (used by diffuse and metal fuzz)
static float3 rng_sphere(thread uint& s) {
    float u = rng(s);
    float v = rng(s);
    float theta = 2.0f * M_PI_F * u;
    float phi   = acos(1.0f - 2.0f * v);
    float sp = sin(phi), cp = cos(phi);
    return float3(sp * cos(theta), sp * sin(theta), cp);
}

// ---------------------------------------------------------------------------
// Ray / hit structs
// ---------------------------------------------------------------------------

struct GPURay { float3 org; float3 dir; };

struct Hit {
    float  t;
    float3 p;
    float3 n;
    bool   exit;
    bool   valid;
};

// ---------------------------------------------------------------------------
// Geometry intersection — mirrors CPU algorithms exactly
// ---------------------------------------------------------------------------

static Hit hit_sphere(GPURay r, float minT, float maxT,
                      device const GPUObject& obj)
{
    float3 center = float3(obj.d[0], obj.d[1], obj.d[2]);
    float  radius = obj.d[3];

    float3 rts   = center - r.org;
    float  a     = dot(r.dir, r.dir);
    float  h     = dot(r.dir, rts);
    float  c     = dot(rts, rts) - radius * radius;
    float  delta = h * h - a * c;

    Hit res; res.valid = false;
    if (delta < 1e-8f) return res;

    float sqrtd = sqrt(delta);
    float invA  = 1.0f / a;
    float t     = (h - sqrtd) * invA;
    if (t < minT) t = (h + sqrtd) * invA;
    if (t < minT || t > maxT) return res;

    res.t   = t;
    res.p   = r.org + t * r.dir;
    float3 outN = (res.p - center) / radius;
    bool   ex   = dot(r.dir, outN) > 0.0f;
    res.exit  = ex;
    res.n     = ex ? -outN : outN;
    res.valid = true;
    return res;
}

static Hit hit_triangle(GPURay r, float minT, float maxT,
                        device const GPUObject& obj)
{
    float3 a  = float3(obj.d[0], obj.d[1], obj.d[2]);
    float3 b  = float3(obj.d[3], obj.d[4], obj.d[5]);
    float3 c  = float3(obj.d[6], obj.d[7], obj.d[8]);
    float3 ab = b - a;
    float3 ac = c - a;
    float3 n  = normalize(cross(ab, ac));

    float3 pvec   = cross(r.dir, ac);
    float  det    = dot(ab, pvec);

    Hit res; res.valid = false;
    if (fabs(det) < 1e-8f) return res;

    float  invDet = 1.0f / det;
    float3 tvec   = r.org - a;
    float  u      = dot(tvec, pvec) * invDet;
    if (u < 0.0f || u > 1.0f) return res;

    float3 qvec = cross(tvec, ab);
    float  v    = dot(r.dir, qvec) * invDet;
    if (v < 0.0f || u + v > 1.0f) return res;

    float t = dot(ac, qvec) * invDet;
    if (t < minT || t > maxT) return res;

    res.t   = t;
    res.p   = r.org + t * r.dir;
    bool ex = dot(r.dir, n) > 0.0f;
    res.exit  = ex;
    res.n     = ex ? -n : n;
    res.valid = true;
    return res;
}

static Hit hit_quad(GPURay r, float minT, float maxT,
                    device const GPUObject& obj)
{
    float3 center = float3(obj.d[0], obj.d[1], obj.d[2]);
    float3 u      = float3(obj.d[3], obj.d[4], obj.d[5]);
    float3 v      = float3(obj.d[6], obj.d[7], obj.d[8]);
    float3 origin = center - u * 0.5f - v * 0.5f;
    float3 n      = normalize(cross(u, v));
    float  uu     = dot(u, u);
    float  vv     = dot(v, v);
    float  uv     = dot(u, v);
    float  invD   = 1.0f / (uu * vv - uv * uv);

    Hit res; res.valid = false;
    float denom = dot(r.dir, n);
    if (fabs(denom) < 1e-8f) return res;

    float  t = dot(center - r.org, n) / denom;
    if (t < minT || t > maxT) return res;

    float3 p  = r.org + t * r.dir - origin;
    float  pu = dot(p, u);
    float  pv = dot(p, v);
    float  s  = (pu * vv - pv * uv) * invD;
    float  w  = (pv * uu - pu * uv) * invD;
    if (s < 0.0f || s > 1.0f || w < 0.0f || w > 1.0f) return res;

    res.t   = t;
    res.p   = r.org + t * r.dir;
    bool ex = dot(r.dir, n) > 0.0f;
    res.exit  = ex;
    res.n     = ex ? -n : n;
    res.valid = true;
    return res;
}

// ---------------------------------------------------------------------------
// Scene traversal
// ---------------------------------------------------------------------------

struct SceneHit {
    Hit    h;
    int    matType;
    float3 color;
    float  param;
};

static SceneHit scene_hit(GPURay r,
                           device const GPUObject* objects,
                           int count)
{
    SceneHit res;
    res.h.valid = false;
    res.h.t     = 1e30f;

    for (int i = 0; i < count; i++) {
        Hit h;
        device const GPUObject& obj = objects[i];
        if      (obj.type == 0) h = hit_sphere(r,   1e-4f, res.h.t, obj);
        else if (obj.type == 1) h = hit_triangle(r, 1e-4f, res.h.t, obj);
        else                    h = hit_quad(r,     1e-4f, res.h.t, obj);

        if (h.valid) {
            res.h       = h;
            res.matType = obj.matType;
            res.color   = float3(obj.cr, obj.cg, obj.cb);
            res.param   = obj.param;
        }
    }
    return res;
}

// ---------------------------------------------------------------------------
// Optics — mirrors math/util.cpp
// ---------------------------------------------------------------------------

static float3 diffuse_dir(float3 normal, thread uint& s) {
    float3 uv = rng_sphere(s);
    float3 v  = normal + uv;
    if (length_squared(v) < 1e-8f) return normal;
    return normalize(v);
}

static float3 reflect_dir(float3 v, float3 n) {
    return v - 2.0f * dot(v, n) * n;
}

static float schlick(float cosTheta, float n1, float n2) {
    float r0 = (n1 - n2) / (n1 + n2);
    r0 *= r0;
    return r0 + (1.0f - r0) * pow(1.0f - cosTheta, 5.0f);
}

static float3 refract_dir(float3 dir, float3 normal,
                           float n1, float n2, thread uint& s)
{
    float cosTheta = dot(-dir, normal);
    float sinTheta = sqrt(max(0.0f, 1.0f - cosTheta * cosTheta));
    float idx      = n1 / n2;
    if (sinTheta * idx > 1.0f || schlick(cosTheta, n1, n2) > rng(s)) {
        // Total internal reflection
        return dir + 2.0f * cosTheta * normal;
    }
    float3 perp = idx * (dir + cosTheta * normal);
    float3 para = -sqrt(fabs(1.0f - length_squared(perp))) * normal;
    return perp + para;
}

// ---------------------------------------------------------------------------
// Sky and gamma — match main.cpp / math/util.cpp
// ---------------------------------------------------------------------------

static float3 sky_color(float3 dir) {
    float a = 0.5f * (dir.y + 1.0f);
    return (1.0f - a) * float3(1.0f) + a * float3(0.5f, 0.7f, 1.0f);
}

static float gamma_correct(float val) {
    if (val <= 0.0f)        return 0.0f;
    if (val <= 0.0031308f)  return 12.92f * val;
    return 1.055f * pow(val, 1.0f / 2.4f) - 0.055f;
}

// ---------------------------------------------------------------------------
// Compute kernel — one thread per pixel
// ---------------------------------------------------------------------------

kernel void pathtrace(
    device const GPUObject*        objects [[ buffer(0) ]],
    device const GPURenderParams*  params  [[ buffer(1) ]],
    texture2d<float, access::write> outTex [[ texture(0) ]],
    uint2 gid [[ thread_position_in_grid ]])
{
    int W = params->width;
    int H = params->height;
    if ((int)gid.x >= W || (int)gid.y >= H) return;

    float3 camPos = float3(params->camPosX, params->camPosY, params->camPosZ);
    float3 origin = float3(params->originX, params->originY, params->originZ);
    float3 deltaW = float3(params->deltaWX, params->deltaWY, params->deltaWZ);
    float3 deltaH = float3(params->deltaHX, params->deltaHY, params->deltaHZ);
    int    nSamples   = params->samplesPerPixel;
    int    maxBounces = params->maxBounces;
    int    nObjects   = params->objectCount;

    float3 accum = float3(0.0f);

    for (int sampleIdx = 0; sampleIdx < nSamples; sampleIdx++) {
        uint seed = (gid.x * 1973u + gid.y * 9277u + (uint)sampleIdx * 26699u) | 1u;

        float  jx   = rng(seed) - 0.5f;
        float  jy   = rng(seed) - 0.5f;
        float3 pixP = origin + deltaW * (float(gid.x) + jx)
                             + deltaH * (float(gid.y) + jy);

        GPURay r;
        r.org = camPos;
        r.dir = normalize(pixP - camPos);

        float3 color  = float3(1.0f);
        bool   hitSky = false;

        for (int b = 0; b < maxBounces; b++) {
            SceneHit sh = scene_hit(r, objects, nObjects);
            if (!sh.h.valid) {
                color *= sky_color(r.dir);
                hitSky = true;
                break;
            }

            float3 newDir;
            if (sh.matType == 0) {
                // Diffuse (Lambertian)
                newDir = diffuse_dir(sh.h.n, seed);
            } else if (sh.matType == 1) {
                // Metal
                newDir = reflect_dir(r.dir, sh.h.n) + rng_sphere(seed) * sh.param;
            } else {
                // Dielectric
                float n1 = sh.h.exit ? sh.param : 1.0f;
                float n2 = sh.h.exit ? 1.0f     : sh.param;
                newDir = refract_dir(r.dir, sh.h.n, n1, n2, seed);
            }

            color *= sh.color;
            r.org  = sh.h.p;
            r.dir  = normalize(newDir);
        }

        if (!hitSky) color = float3(0.0f); // max depth exceeded → black

        accum += color;
    }

    accum /= float(nSamples);
    accum  = float3(gamma_correct(accum.x),
                    gamma_correct(accum.y),
                    gamma_correct(accum.z));
    accum  = clamp(accum, 0.0f, 1.0f);

    outTex.write(float4(accum, 1.0f), gid);
}
