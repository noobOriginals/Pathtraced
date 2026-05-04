#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#define CULLING

// Std includes
#include <cmath>

// Local includes
#include "types.h"
#include "m3d.hpp"
#include "optics.hpp"

struct Ray {
    m3d::vec3 orig, dir;
    float32 refIdx; // For dielectrics

    Ray() = default;
    Ray(m3d::vec3 origin, m3d::vec3 direction) : orig(origin), dir(direction) {
        refIdx = OPTICS_AIR_REF_IDX;
    }
    Ray(m3d::vec3 origin, m3d::vec3 direction, float32 refIdx) : orig(origin), dir(direction), refIdx(refIdx) {}

    m3d::vec3 at(float32 t) const {
        return orig + dir * t;
    }
};

struct Hitpoint {
    float32 t;
    m3d::vec3 p, normal;

    Hitpoint() = default;
    Hitpoint(float32 t, m3d::vec3 p, m3d::vec3 normal) : t(t), p(p), normal(normal) {}
};

class Object {
public:
    virtual bool hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const = 0;
};

class Sphere : public Object {
public:
    Sphere() = default;
    Sphere(m3d::vec3 origin, float32 radius);

    bool hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const override;

    const m3d::vec3& getOrigin() const;
    const float32& getRadius() const;

private:
    m3d::vec3 origin;
    float32 radius;
};

class Triangle : public Object {
public:
    Triangle() = default;
    Triangle(m3d::vec3 a, m3d::vec3 b, m3d::vec3 c);

    bool hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const override;

    const m3d::vec3& getA() const;
    const m3d::vec3& getB() const;
    const m3d::vec3& getC() const;
    const m3d::vec3& getAB() const;
    const m3d::vec3& getAC() const;
    const m3d::vec3& getNormal() const;

private:
    m3d::vec3 a, b, c, ab, ac, normal;
};

class Quad : public Object {
public:
    Quad() = default;
    Quad(m3d::vec3 center, m3d::vec3 u, m3d::vec3 v);

    bool hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const override;

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
