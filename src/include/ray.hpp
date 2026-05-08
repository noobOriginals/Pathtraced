#ifndef RAY_HPP
#define RAY_HPP

// Local includes
#include <lib/m3d.hpp>

struct Ray {
    m3d::vec3 org;
    m3d::vec3 dir;

    Ray() = default;
    Ray(const m3d::vec3& origin, const m3d::vec3& direction);

    m3d::vec3 at(m3d::float32 t) const;
};

#endif // RAY_HPP