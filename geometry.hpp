#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#define CULLING

// Std includes
#include <cmath>

// Local includes
#include "m3d.hpp"
#include "optics.hpp"

#define SPHERE 0x1
#define TRIANGLE 0x2
#define QUAD 0x3

struct Ray {
    m3d::vec3 orig, dir;

    Ray() = default;
    Ray(m3d::vec3 origin, m3d::vec3 direction) : orig(origin), dir(normalize(direction)) {}

    m3d::vec3 at(m3d::float32 t) const {
        return orig + dir * t;
    }
};

struct Hitpoint {
    m3d::float32 t;
    m3d::vec3 p, normal;

    Hitpoint() = default;
    Hitpoint(m3d::float32 t, m3d::vec3 p, m3d::vec3 normal) : t(t), p(p), normal(normalize(normal)) {}
};

class Hittable {
public:
    virtual bool hitRay(const Ray& ray, Hitpoint* hp, m3d::float32 minT, m3d::float32 maxT) const = 0;
    virtual m3d::int32 type() const = 0;
};

class Sphere : public Hittable {
public:
    Sphere() = default;
    Sphere(m3d::vec3 origin, m3d::float32 radius);

    bool hitRay(const Ray& ray, Hitpoint* hp, m3d::float32 minT, m3d::float32 maxT) const override;

    const m3d::vec3& getOrigin() const;
    const m3d::float32& getRadius() const;

    // Type
    m3d::int32 type() const override {
        return SPHERE;
    }

private:
    m3d::vec3 origin;
    m3d::float32 radius;
};

class Triangle : public Hittable {
public:
    Triangle() = default;
    Triangle(m3d::vec3 a, m3d::vec3 b, m3d::vec3 c);

    bool hitRay(const Ray& ray, Hitpoint* hp, m3d::float32 minT, m3d::float32 maxT) const override;

    const m3d::vec3& getA() const;
    const m3d::vec3& getB() const;
    const m3d::vec3& getC() const;
    const m3d::vec3& getAB() const;
    const m3d::vec3& getAC() const;
    const m3d::vec3& getNormal() const;

    // Name
    m3d::int32 type() const override {
        return TRIANGLE;
    }

private:
    m3d::vec3 a, b, c, ab, ac, normal;
};

class Quad : public Hittable {
public:
    Quad() = default;
    Quad(m3d::vec3 center, m3d::vec3 u, m3d::vec3 v);

    bool hitRay(const Ray& ray, Hitpoint* hp, m3d::float32 minT, m3d::float32 maxT) const override;

    const m3d::vec3& getCenter() const;
    const m3d::vec3& getOrigin() const;
    const m3d::vec3& getU() const;
    const m3d::vec3& getV() const;
    const m3d::vec3& getNormal() const;

    // Name
    m3d::int32 type() const override {
        return QUAD;
    }

private:
    m3d::vec3 center, origin, u, v, normal;
    m3d::float32 uu, vv, uv, invProjectionDenom;
};

#endif // GEOMETRY_HPP
