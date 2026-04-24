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
    Sphere(Vec3 center, float32 radius);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const Vec3& getCenter() const;
    const float32& getRadius() const;

private:
    Vec3 center;
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

private:
    Vec3 a, b, c;
};

// TODO: Finish Quad implementation
class Quad {
public:
    Quad() = default;
    Quad(Vec3 center, Vec3 edge0, Vec3 edge1);

    bool hitRay(const Ray& ray, Hitpoint* hp) const;

    const Vec3& getCenter() const;
    const Vec3& getEdge0() const;
    const Vec3& getEdge1() const;

private:
    Vec3 center, edge0, edge1;
};

#endif // GEOMETRY_HPP
