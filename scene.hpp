#ifndef SCENE_HPP
#define SCENE_HPP

// Std includes
#include <vector>

// Local includes
#include "m3d.hpp"
#include "materials.hpp"
#include "geometry.hpp"

struct Body {
    Object* obj;
    Material* mat;

    Body(Object* obj, Material* mat) : obj(obj), mat(mat) {}

    bool hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const {
        return obj->hitRay(ray, hp, minT, maxT);
    }
};

typedef std::vector<Body> Scene;

Material* traceScene(const Scene& scene, const Ray& ray, Hitpoint* hp) {
    Material* mat = nullptr;
    m3d::float32 closestT = MAXFLOAT;
    for (const Body& b : scene) {
        if (b.hitRay(ray, hp, m3d::EPSILON, closestT)) {
            mat = b.mat;
            closestT = hp->t;
        }
    }
    return mat;
}

#endif // SCENE_HPP