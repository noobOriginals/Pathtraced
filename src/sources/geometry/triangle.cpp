#include <geometry/triangle.hpp>

// Std includes
#include <cmath>

using namespace m3d;

namespace geo {

// Triangle

Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c) : a(a), b(b), c(c) {
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

} // namespace geo
