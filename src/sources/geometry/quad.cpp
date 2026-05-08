#include <geometry/quad.hpp>

// Std includes
#include <cmath>

using namespace m3d;

namespace geo {

// Quad

Quad::Quad(const vec3& center, const vec3& u, const vec3& v) : center(center), u(u), v(v) {
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

} // namespace geo
