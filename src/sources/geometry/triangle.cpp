#include <geometry/triangle.hpp>

// Std includes
#include <cmath>

using namespace m3d;
using namespace math;

namespace geo {

// Triangle

Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c) : a(a), b(b), c(c) {
    ab = b - a;
    ac = c - a;
    normal = normalize(cross(ab, ac));
}

Hittable* Triangle::clone() const {
    return new Triangle(*this);
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

int Triangle::getType() const { return 1; }
vec3 Triangle::getA() const { return a; }
vec3 Triangle::getB() const { return b; }
vec3 Triangle::getC() const { return c; }

std::string Triangle::toString() const {
    std::string str = "Triangle ";
    str += std::to_string(a.x) + " ";
    str += std::to_string(a.y) + " ";
    str += std::to_string(a.z) + " ";
    str += std::to_string(b.x) + " ";
    str += std::to_string(b.y) + " ";
    str += std::to_string(b.z) + " ";
    str += std::to_string(c.x) + " ";
    str += std::to_string(c.y) + " ";
    str += std::to_string(c.z);
    return str;
}

} // namespace geo
