#ifndef SCENE_HPP
#define SCENE_HPP

// Std includes
#include <vector>

// Local includes
#include <ray.hpp>
#include <hitpoint.hpp>
#include <material/material.hpp>
#include <scene/object.hpp>

namespace scene {

class Scene {
public:
    Scene() = default;

    void add(const Object& obj);

    mat::Material* getClosestHit(const Ray& ray, Hitpoint& hp) const;

private:
    std::vector<Object> objects;
};

} // namespace scene

#endif // SCENE_HPP