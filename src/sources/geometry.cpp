#include "geometry.hpp"

// Std includes
#include <cmath>

// Local includes
#include "util.hpp"

using namespace m3d;

// Sphere

Sphere::Sphere(const m3d::vec3& center, m3d::float32 radius) : center(center), radius(radius) {}

bool Sphere::hit(const Ray& ray, Hitpoint& hp, float32 minT, float32 maxT) const {
    vec3 rayToSphere = center - ray.org;

    float32 a = lenSq(ray.dir);
    float32 h = dot(ray.dir, rayToSphere);
    float32 c = lenSq(rayToSphere) - radius * radius;
    float32 delta = h * h - a * c;

    if (delta < EPSILON) {
        return false;
    }

    float32 sqrtd = std::sqrt(delta);
    float32 invA = 1.0 / a;

    hp.t = (h - sqrtd) * invA;

    if (hp.t < EPSILON) {
        hp.t = (h + sqrtd) * invA;
    }

    if (hp.t < minT || hp.t > maxT) {
        return false;
    }

    hp.p = ray.at(hp.t);
    hp.setNormal(ray.dir, (hp.p - center) / radius);

    return true;
}

// Triangle

Triangle::Triangle(const m3d::vec3& a, const m3d::vec3& b, const m3d::vec3& c) : a(a), b(b), c(c) {
    ab = b - a;
    ac = c - a;
    normal = normalize(cross(ab, ac));
}

bool Triangle::hit(const Ray& ray, Hitpoint& hp, float32 minT, float32 maxT) const {
    vec3 pvec = cross(ray.dir, ac);
    float32 det = dot(ab, pvec);

    if (std::fabs(det) < EPSILON) {
        return false;
    }

    float32 invDet = 1.0 / det;

    vec3 tvec = ray.org - a;
    float32 u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) {
        return false;
    }

    vec3 qvec = cross(tvec, ab);
    float32 v = dot(ray.dir, qvec) * invDet;
    if (v < 0 || u + v > 1) {
        return false;
    }

    hp.t = dot(ac, qvec) * invDet;

    if (hp.t < minT || hp.t > maxT) {
        return false;
    }

    hp.p = ray.at(hp.t);
    hp.setNormal(ray.dir, normal);

    return true;
}

// Quad

Quad::Quad(const m3d::vec3& center, const m3d::vec3& u, const m3d::vec3& v) : center(center), u(u), v(v) {
    origin = center - u * 0.5 - v * 0.5;
    normal = normalize(cross(u, v));
    uu = lenSq(u);
    vv = lenSq(v);
    uv = dot(u, v);
    invProjectionDenom = 1.0 / (uu * vv - uv * uv);
}

bool Quad::hit(const Ray& ray, Hitpoint& hp, float32 minT, float32 maxT) const {
    float32 denom = dot(ray.dir, normal);

    if (std::fabs(denom) < EPSILON) {
        return false;
    }

    float32 t = dot(center - ray.org, normal) / denom;

    if (t < minT || t > maxT) {
        return false;
    }

    vec3 p = ray.at(t) - origin;

    float32 pu = dot(p, u);
    float32 pv = dot(p, v);

    float32 s = (pu * vv - pv * uv) * invProjectionDenom;
    float32 w = (pv * uu - pu * uv) * invProjectionDenom;

    if (s < 0 || s > 1 || w < 0 || w > 1) {
        return false;
    }

    hp.t = t;
    hp.p = ray.at(t);
    hp.setNormal(ray.dir, normal);

    return true;
}
