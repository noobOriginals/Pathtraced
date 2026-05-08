#ifndef SCENE_HPP
#define SCENE_HPP

// Std includes
#include <vector>
#include <string>

// Local includes
#include <ray.hpp>
#include <hitpoint.hpp>
#include <material/material.hpp>
#include <scene/object.hpp>

namespace scene {

class Scene {
public:
    Scene() = default;
    Scene(std::string filepath);
    ~Scene();

    void add(const Object& obj);
    mat::Material* getClosestHit(const Ray& ray, Hitpoint& hp) const;
    void save(std::string filepath) const;

private:
    std::vector<Object> objects;
    bool loadedFromFile = false;
    m3d::int32 numLoaded;
};

} // namespace scene

#endif // SCENE_HPP