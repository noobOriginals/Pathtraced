#include <geometry/quad.hpp>

// Std includes
#include <cmath>

using namespace m3d;
using namespace math;

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

Hittable* Quad::clone() const {
    return new Quad(*this);
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

std::string Quad::toString() const {
    std::string str = "Quad ";
    str += std::to_string(center.x) + " ";
    str += std::to_string(center.y) + " ";
    str += std::to_string(center.z) + " ";
    str += std::to_string(u.x) + " ";
    str += std::to_string(u.y) + " ";
    str += std::to_string(u.z) + " ";
    str += std::to_string(v.x) + " ";
    str += std::to_string(v.y) + " ";
    str += std::to_string(v.z);
    return str;
}

} // namespace geo
