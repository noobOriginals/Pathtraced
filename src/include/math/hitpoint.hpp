#ifndef MATH_HITPOINT_HPP
#define MATH_HITPOINT_HPP

// Local includes
#include <lib/m3d.hpp>

namespace math {

struct Hitpoint {
    m3d::float32 t;
    m3d::vec3 p, normal;
    bool exit = false;

    Hitpoint() = default;

    void setNormal(const m3d::vec3& dir, const m3d::vec3& n);
};

} // namespace math

#endif // MATH_HITPOINT_HPP