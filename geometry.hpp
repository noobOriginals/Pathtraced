#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

// Std includes

// Local includes
#include "types.h"
#include "math.hpp"

struct Ray {
    Vec3 orig, dir;

    Ray() = default;
    Ray(Vec3 origin, Vec3 direction) {
        orig = origin;
        dir = direction;
    }

    Vec3 at(float32 t) const {
        return orig + dir * t;
    }
};

struct Hitpoint {
    float32 t;
    Vec3 normal;

    Hitpoint() = default;
    Hitpoint(float32 t, Vec3 normal) {
        this->t = t;
        this->normal = normal;
    }
};

class Sphere {
public:
    Sphere() = default;
    Sphere(Vec3 origin, float32 radius);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const Vec3& getOrigin() const;
    const float32& getRadius() const;

private:
    Vec3 origin;
    float32 radius;
};

class Triangle {
public:
    Triangle() = default;
    Triangle(Vec3 a, Vec3 b, Vec3 c);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const Vec3& getA() const;
    const Vec3& getB() const;
    const Vec3& getC() const;
    const Vec3& getAB() const;
    const Vec3& getAC() const;
    const Vec3& getNormal() const;

private:
    Vec3 a, b, c, ab, ac, normal;
};

class Quad {
public:
    Quad() = default;
    Quad(Vec3 center, Vec3 u, Vec3 v);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const Vec3& getCenter() const;
    const Vec3& getOrigin() const;
    const Vec3& getU() const;
    const Vec3& getV() const;
    const Vec3& getNormal() const;

private:
    Vec3 center, origin, u, v, normal;
    float32 uu, vv, uv, invProjectionDenom;
};

#endif // GEOMETRY_HPP
