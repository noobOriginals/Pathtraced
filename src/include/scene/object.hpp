#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

// Local includesd
#include <lib/m3d.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>
#include <geometry/hittable.hpp>
#include <material/material.hpp>

namespace scene {

struct Object {
    geo::Hittable* h = nullptr;
    mat::Material* m = nullptr;

    Object() = default;
    Object(geo::Hittable* h, mat::Material* m);

    bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const;
};

} // namespace scene

#endif