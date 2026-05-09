#ifndef MAT_SCATTER_RESULT_HPP
#define MAT_SCATTER_RESULT_HPP

// Local includes
#include <lib/m3d.hpp>
#include <math/ray.hpp>

namespace mat {

struct ScatterResult {
    math::Ray ray;
    m3d::vec3 color;
    bool scattered;

    ScatterResult() = default;
    ScatterResult(const math::Ray& ray, const m3d::vec3& color, bool scattered);
};

} // namespace mat

#endif // MATERIAL_HPP
