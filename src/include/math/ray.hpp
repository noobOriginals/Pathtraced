#ifndef MATH_RAY_HPP
#define MATH_RAY_HPP

// Local includes
#include <lib/m3d.hpp>

namespace math {

struct Ray {
    m3d::vec3 org;
    m3d::vec3 dir;

    Ray() = default;
    Ray(const m3d::vec3& origin, const m3d::vec3& direction);

    m3d::vec3 at(m3d::float32 t) const;
};

} // namespace math

#endif // MATH_RAY_HPP