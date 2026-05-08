#ifndef UTIL_HPP
#define UTIL_HPP

// Local includes
#include <lib/m3d.hpp>

// Random utility

m3d::float32 randomUnit();
m3d::vec3 randomUV();
m3d::vec3 randomOnHemisphere(const m3d::vec3& normal);
m3d::vec3 randomCosineHemisphere(const m3d::vec3& normal);

// Optics

#define UTIL_AIR_REF_IDX 1.0f

m3d::vec3 diffuse(const m3d::vec3& normal);
m3d::vec3 reflect(const m3d::vec3& v, const m3d::vec3& normal);
m3d::vec3 refract(const m3d::vec3& dir, const m3d::vec3& normal, m3d::float32 n1, m3d::float32 n2);
m3d::float32 reflectance(m3d::float32 cos, m3d::float32 n1, m3d::float32 n2);

#endif // UTIL_HPP