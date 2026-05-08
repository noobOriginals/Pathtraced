#include <ray.hpp>

using namespace m3d;

// Ray

Ray::Ray(const vec3& origin, const vec3& direction) : org(origin), dir(direction) {}

vec3 Ray::at(float32 t) const {
    return org + dir * t;
}
