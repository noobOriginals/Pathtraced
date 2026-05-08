#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

// Local includes
#include "m3d.hpp"

struct Ray {
    m3d::vec3 org;
    m3d::vec3 dir;

    Ray() = default;
    Ray(const m3d::vec3& origin, const m3d::vec3& direction) : org(origin), dir(direction) {}

    m3d::vec3 at(m3d::float32 t) const {
        return org + dir * t;
    }
};

struct Hitpoint {
    m3d::float32 t;
    m3d::vec3 p, normal;
    bool exit = false;

    void setNormal(const m3d::vec3& dir, const m3d::vec3& n) {
        if (m3d::dot(dir, n) > 0) {
            exit = true;
            normal = -n;
        } else {
            exit = false;
            normal = n;
        }
    }
};

class Hittable {
public:
    virtual ~Hittable() {}
    virtual bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const = 0;
};

class Sphere : public Hittable {
public:
    Sphere() = default;
    Sphere(const m3d::vec3& center, m3d::float32 radius);

    bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const override;

private:
    m3d::vec3 center;
    m3d::float32 radius;
};

class Triangle : public Hittable {
public:
    Triangle() = default;
    Triangle(const m3d::vec3& a, const m3d::vec3& b, const m3d::vec3& c);

    bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const override;

private:
    m3d::vec3 a, b, c, ab, ac, normal;
};

class Quad : public Hittable {
public:
    Quad() = default;
    Quad(const m3d::vec3& center, const m3d::vec3& u, const m3d::vec3& v);

    bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const override;

private:
    m3d::vec3 center, origin, u, v, normal;
    m3d::float32 uu, vv, uv, invProjectionDenom;
};

#endif // GEOMETRY_HPP
