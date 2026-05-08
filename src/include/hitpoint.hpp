#ifndef HITPOINT_HPP
#define HITPOINT_HPP

// Local includes
#include <lib/m3d.hpp>

struct Hitpoint {
    m3d::float32 t;
    m3d::vec3 p, normal;
    bool exit = false;

    Hitpoint() = default;

    void setNormal(const m3d::vec3& dir, const m3d::vec3& n);
};

#endif // HITPOINT_HPP