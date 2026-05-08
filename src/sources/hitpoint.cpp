#include <hitpoint.hpp>

using namespace m3d;

// Hitpoint

void Hitpoint::setNormal(const vec3& dir, const vec3& n) {
    if (dot(dir, n) > 0) {
        exit = true;
        normal = -n;
    } else {
        exit = false;
        normal = n;
    }
}
