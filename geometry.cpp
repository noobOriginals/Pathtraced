#include "geometry.hpp"

// Std includes
#include <cmath>

// Local includes
#include "util.hpp"

// Sphere

Sphere::Sphere(Vec3 center, float32 radius) {
    this->center = center;
    this->radius = radius;
}

bool Sphere::hitRay(const Ray& ray, Hitpoint* hp) const {
    Vec3 rayToSphere = center - ray.orig;
    float32 a = lenSq(ray.dir);
    float32 h = dot(ray.dir, rayToSphere);
    float32 c = lenSq(rayToSphere) - radius * radius;
    float32 delta = h * h - a * c;
    if (delta < UTIL_EPSILON) {
        return false;
    } else {
        hp->t = (h - std::sqrt(delta)) * a;
        hp->normal = normalize(center - ray.at(hp->t));
        return true;
    }
}

const Vec3& Sphere::getCenter() const {
    return center;
}

const float32& Sphere::getRadius() const {
    return radius;
}

// Triangle

Triangle::Triangle(Vec3 a, Vec3 b, Vec3 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

bool Triangle::hitRay(const Ray& ray, Hitpoint* hp) const {
    Vec3 ab = b - a;
    Vec3 ac = c - a;
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
    hp->normal = normalize(cross(ab, ac));

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

// Quad

Quad::Quad(Vec3 center, Vec3 edge0, Vec3 edge1) {
    this->center = center;
    this->edge0 = edge0;
    this->edge1 = edge1;
}

bool Quad::hitRay(const Ray& ray, Hitpoint* hp) const {
    Vec3 normal = cross(edge0, edge1);
    float32 denom = dot(ray.dir, normal);

    if (denom >= -UTIL_EPSILON) {
        return false;
    }

    float32 t = dot(center - ray.orig, normal) / denom;
    Vec3 p = center - ray.at(t);
}

const Vec3& Quad::getCenter() const {
    return center;
}

const Vec3& Quad::getEdge0() const {
    return edge0;
}

const Vec3& Quad::getEdge1() const {
    return edge1;
}
