#include "geometry.hpp"

// Std includes
#include <cmath>

// Local includes
#include "util.hpp"

// Sphere

Sphere::Sphere(Vec3 origin, float32 radius) {
    this->origin = origin;
    this->radius = radius;
}

bool Sphere::hitRay(const Ray& ray, Hitpoint* hp) const {
    Vec3 rayToSphere = origin - ray.orig;

    float32 a = lenSq(ray.dir);
    float32 h = dot(ray.dir, rayToSphere);
    float32 c = lenSq(rayToSphere) - radius * radius;
    float32 delta = h * h - a * c;

    if (delta < UTIL_EPSILON) {
        return false;
    }

    hp->t = (h - std::sqrt(delta)) * a;
    hp->normal = (origin - ray.at(hp->t)) / radius;

    return true;
}

const Vec3& Sphere::getOrigin() const {
    return origin;
}

const float32& Sphere::getRadius() const {
    return radius;
}

// Triangle

Triangle::Triangle(Vec3 a, Vec3 b, Vec3 c) {
    this->a = a;
    this->b = b;
    this->c = c;
    ab = b - a;
    ac = c - a;
    normal = normalize(cross(ab, ac));
}

bool Triangle::hitRay(const Ray& ray, Hitpoint* hp) const {
    Vec3 pvec = cross(ray.dir, ac);
    float32 det = dot(ab, pvec);

    if (det < UTIL_EPSILON) {
        return false;
    }

    float32 invDet = 1.0 / det;

    Vec3 tvec = ray.orig - a;
    float32 u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) {
        return false;
    }

    Vec3 qvec = cross(tvec, ab);
    float32 v = dot(ray.dir, qvec) * invDet;
    if (v < 0 || u + v > 1) {
        return false;
    }

    hp->t = dot(ac, qvec) * invDet;
    hp->normal = normal;

    return true;
}

const Vec3& Triangle::getA() const {
    return a;
}

const Vec3& Triangle::getB() const {
    return b;
}

const Vec3& Triangle::getC() const {
    return c;
}
const Vec3& Triangle::getAB() const {
    return ab;
}

const Vec3& Triangle::getAC() const {
    return ac;
}

const Vec3& Triangle::getNormal() const {
    return normal;
}

// Quad

Quad::Quad(Vec3 center, Vec3 u, Vec3 v) {
    this->center = center;
    this->u = u;
    this->v = v;
    origin = center - u * 0.5 - v * 0.5;
    normal = normalize(cross(u, v));
    uu = lenSq(u);
    vv = lenSq(v);
    uv = dot(u, v);
    invProjectionDenom = 1.0 / (uu * vv - uv * uv);
}

bool Quad::hitRay(const Ray& ray, Hitpoint* hp) const {
    float32 denom = dot(ray.dir, normal);

    if (denom > -UTIL_EPSILON) {
        return false;
    }

    float32 t = dot(center - ray.orig, normal) / denom;
    Vec3 p = ray.at(t) - origin;

    float32 pu = dot(p, u);
    float32 pv = dot(p, v);

    float32 s = (pu * vv - pv * uv) * invProjectionDenom;
    float32 w = (pv * uu - pu * uv) * invProjectionDenom;

    if (s < 0 || s > 1 || w < 0 || w > 1) {
        return false;
    }

    hp->t = t;
    hp->normal = normal;

    return true;
}

const Vec3& Quad::getCenter() const {
    return center;
}

const Vec3& Quad::getOrigin() const {
    return origin;
}

const Vec3& Quad::getU() const {
    return u;
}

const Vec3& Quad::getV() const {
    return v;
}

const Vec3& Quad::getNormal() const {
    return normal;
}
