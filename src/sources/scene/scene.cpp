#include <scene/scene.hpp>

// Local includes
#include <lib/m3d.hpp>

using namespace m3d;

namespace scene {

// Scene

void Scene::add(const Object& obj) {
    objects.push_back(obj);
}

mat::Material* Scene::getClosestHit(const Ray& ray, Hitpoint& hp) const {
    mat::Material* mat = nullptr;
    float32 closestT = std::numeric_limits<float32>::max();
    for (const Object& obj : objects) {
        if (obj.hit(ray, hp, 1e-4f, closestT)) {
            mat = obj.m;
            closestT = hp.t;
        }
    }
    return mat;
}

} // namespace scene