#include <scene/object.hpp>

using namespace m3d;
using namespace math;

namespace scene {

// Object

Object::Object(geo::Hittable* h, mat::Material* m) : h(h), m(m) {}

bool Object::hit(const Ray& ray, Hitpoint& hp, float32 minT, float32 maxT) const {
    return h->hit(ray, hp, minT, maxT);
}

} // namespace scene
