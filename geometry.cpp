#include "geometry.hpp"

// Std includes
#include <cmath>

// Local includes
#include "util.hpp"

using namespace m3d;

// Sphere

Sphere::Sphere(vec3 origin, float32 radius) {
    this->origin = origin;
    this->radius = radius;
}

bool Sphere::hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const {
    vec3 rayToSphere = origin - ray.orig;

    float32 a = lenSq(ray.dir);
    float32 h = dot(ray.dir, rayToSphere);
    float32 c = lenSq(rayToSphere) - radius * radius;
    float32 delta = h * h - a * c;

    if (delta < EPSILON) {
        return false;
    }

    float32 sqrtd = std::sqrt(delta);
    float32 invA = 1.0 / a;

    hp->t = (h - sqrtd) * invA;

    if (hp->t < EPSILON) {
        hp->t = (h + sqrtd) * invA;
    }

    if (hp->t < minT || hp->t > maxT) {
        return false;
    }

    hp->p = ray.at(hp->t);
    hp->normal = (hp->p - origin) / radius;

    return true;
}

const vec3& Sphere::getOrigin() const {
    return origin;
}

const float32& Sphere::getRadius() const {
    return radius;
}

// Triangle

Triangle::Triangle(vec3 a, vec3 b, vec3 c) {
    this->a = a;
    this->b = b;
    this->c = c;
    ab = b - a;
    ac = c - a;
    normal = normalize(cross(ab, ac));
}

bool Triangle::hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const {
    vec3 pvec = cross(ray.dir, ac);
    float32 det = dot(ab, pvec);

#ifndef CULLING
    if (std::fabs(det) < EPSILON) {
#else
    if (det < EPSILON) {
#endif
        return false;
    }

    float32 invDet = 1.0 / det;

    vec3 tvec = ray.orig - a;
    float32 u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) {
        return false;
    }

    vec3 qvec = cross(tvec, ab);
    float32 v = dot(ray.dir, qvec) * invDet;
    if (v < 0 || u + v > 1) {
        return false;
    }

    hp->t = dot(ac, qvec) * invDet;

    if (hp->t < minT || hp->t > maxT) {
        return false;
    }

    hp->p = ray.at(hp->t);
    hp->normal = normal;

    return true;
}

const vec3& Triangle::getA() const {
    return a;
}

const vec3& Triangle::getB() const {
    return b;
}

const vec3& Triangle::getC() const {
    return c;
}
const vec3& Triangle::getAB() const {
    return ab;
}

const vec3& Triangle::getAC() const {
    return ac;
}

const vec3& Triangle::getNormal() const {
    return normal;
}

// Quad

Quad::Quad(vec3 center, vec3 u, vec3 v) {
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

bool Quad::hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const {
    float32 denom = dot(ray.dir, normal);

#ifndef CULLING
    if (std::fabs(denom) < EPSILON) {
#else
    if (denom > -EPSILON) {
#endif
        return false;
    }

    float32 t = dot(center - ray.orig, normal) / denom;
    vec3 p = ray.at(t) - origin;

    float32 pu = dot(p, u);
    float32 pv = dot(p, v);

    float32 s = (pu * vv - pv * uv) * invProjectionDenom;
    float32 w = (pv * uu - pu * uv) * invProjectionDenom;

    if (s < 0 || s > 1 || w < 0 || w > 1) {
        return false;
    }

    if (t < minT || t > maxT) {
        return false;
    }

    hp->t = t;
    hp->p = ray.at(hp->t);
    hp->normal = normal;

    return true;
}

const vec3& Quad::getCenter() const {
    return center;
}

const vec3& Quad::getOrigin() const {
    return origin;
}

const vec3& Quad::getU() const {
    return u;
}

const vec3& Quad::getV() const {
    return v;
}

const vec3& Quad::getNormal() const {
    return normal;
}
