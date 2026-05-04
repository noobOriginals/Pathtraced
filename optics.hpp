#ifndef OPTICS_HPP
#define OPTICS_HPP

// Std includes
#include <cmath>

// Local includes
#include "m3d.hpp"

#define OPTICS_AIR_REF_IDX 1.0003

// Random utility

m3d::float32 randomUnit();
m3d::vec3 randomUV();
m3d::vec3 randomOnHemisphere(const m3d::vec3& normal);
m3d::vec3 randomCosineHemisphere(const m3d::vec3& normal);

// Optics

m3d::vec3 diffuse(const m3d::vec3& v, const m3d::vec3& normal);
m3d::vec3 reflect(const m3d::vec3& v, const m3d::vec3& normal);
m3d::vec3 refract(const m3d::vec3& dir, const m3d::vec3& normal, m3d::float32 insideRefIdx, m3d::float32 outsideRefIdx);
m3d::vec3 refract(const m3d::vec3& vDir, const m3d::vec3& normal, m3d::float32 refIdx);

#endif // OPTICS_HPP