#include <material/scatter_result.hpp>

using namespace m3d;
using namespace math;

namespace mat {

// ScatterResult

ScatterResult::ScatterResult(const Ray& ray, const vec3& color, bool scattered) : ray(ray), color(color), scattered(scattered) {}

} // namespace mat