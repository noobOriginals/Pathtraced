#ifndef SCENE_HPP
#define SCENE_HPP

// Std includes
#include <vector>
#include <string>

// Local includes
#include <math/ray.hpp>
#include <math/hitpoint.hpp>
#include <material/material.hpp>
#include <scene/object.hpp>

namespace scene {

class Scene {
public:
    Scene() = default;
    Scene(std::string filepath);
    Scene(const Scene& other);
    ~Scene();

    void add(const Object& obj);
    mat::Material* getClosestHit(const math::Ray& ray, math::Hitpoint& hp) const;
    void save(std::string filepath) const;
    const std::vector<Object>& getObjects() const;

    Scene& operator=(const Scene& other);

private:
    std::vector<Object> objects;
    m3d::int32 numLoaded;
};

} // namespace scene

#endif // SCENE_HPP