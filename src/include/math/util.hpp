#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

// Std includes
#include <vector>

// Local includes
#include <lib/m3d.hpp>

namespace math {

// Utility

m3d::float32 gammaCorrect(m3d::float32 val);
m3d::vec3 gammaCorrect(const m3d::vec3& color);
m3d::int32 clamp(m3d::int32 val, m3d::int32 min, m3d::int32 max);
m3d::float32 clamp(m3d::float32 val, m3d::float32 min, m3d::float32 max);
m3d::vec3 clamp(const m3d::vec3& vec, m3d::float32 min, m3d::float32 max);

// Random utility

m3d::float32 randomUnit();
m3d::int32 pickOneOfN(m3d::int32 n);
m3d::int32 pickWeightedOneOfN(const std::vector<m3d::float32>& weights);
m3d::float32 randomUnit(m3d::float32 min, m3d::float32 max);
m3d::vec3 randomVec(const m3d::vec3& min, const m3d::vec3& max);
m3d::vec3 randomUV();
m3d::vec3 randomOnHemisphere(const m3d::vec3& normal);
m3d::vec3 randomCosineHemisphere(const m3d::vec3& normal);

// Optics

#define UTIL_AIR_REF_IDX 1.0f

m3d::vec3 diffuse(const m3d::vec3& normal);
m3d::vec3 reflect(const m3d::vec3& v, const m3d::vec3& normal);
m3d::vec3 refract(const m3d::vec3& dir, const m3d::vec3& normal, m3d::float32 n1, m3d::float32 n2);
m3d::float32 reflectance(m3d::float32 cos, m3d::float32 n1, m3d::float32 n2);

} // namespace math

#endif // MATH_UTIL_HPP