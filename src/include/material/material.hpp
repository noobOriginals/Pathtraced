#ifndef MAT_MATERIAL_HPP
#define MAT_MATERIAL_HPP

// Std includes
#include <string>


// Local includes
#include <lib/m3d.hpp>
#include <math/ray.hpp>
#include <math/hitpoint.hpp>
#include <material/scatter_result.hpp>

namespace mat {

enum MaterialType {
    DIFFUSE,
    METAL,
    DIELECTRIC,
};

struct Material {
    MaterialType type;
    m3d::vec3 color;
    m3d::float32 param;

    Material() = default;
    Material(MaterialType type, const m3d::vec3& color, m3d::float32 param);

    ScatterResult scatter(const math::Ray& ray, const math::Hitpoint& hp) const;

    std::string toString() const;
};

} // namespace mat

#endif // MAT_MATERIAL_HPP
