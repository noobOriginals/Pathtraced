#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

// Std includes

// Local includes
#include "types.h"
#include "m3d.hpp"

struct Ray {
    m3d::vec3 orig, dir;

    Ray() = default;
    Ray(m3d::vec3 origin, m3d::vec3 direction) {
        orig = origin;
        dir = direction;
    }

    m3d::vec3 at(float32 t) const {
        return orig + dir * t;
    }
};

struct Hitpoint {
    float32 t;
    m3d::vec3 normal;

    Hitpoint() = default;
    Hitpoint(float32 t, m3d::vec3 normal) {
        this->t = t;
        this->normal = normal;
    }
};

class Sphere {
public:
    Sphere() = default;
    Sphere(m3d::vec3 origin, float32 radius);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const m3d::vec3& getOrigin() const;
    const float32& getRadius() const;

private:
    m3d::vec3 origin;
    float32 radius;
};

class Triangle {
public:
    Triangle() = default;
    Triangle(m3d::vec3 a, m3d::vec3 b, m3d::vec3 c);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const m3d::vec3& getA() const;
    const m3d::vec3& getB() const;
    const m3d::vec3& getC() const;
    const m3d::vec3& getAB() const;
    const m3d::vec3& getAC() const;
    const m3d::vec3& getNormal() const;

private:
    m3d::vec3 a, b, c, ab, ac, normal;
};

class Quad {
public:
    Quad() = default;
    Quad(m3d::vec3 center, m3d::vec3 u, m3d::vec3 v);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const m3d::vec3& getCenter() const;
    const m3d::vec3& getOrigin() const;
    const m3d::vec3& getU() const;
    const m3d::vec3& getV() const;
    const m3d::vec3& getNormal() const;

private:
    m3d::vec3 center, origin, u, v, normal;
    float32 uu, vv, uv, invProjectionDenom;
};

#endif // GEOMETRY_HPP
