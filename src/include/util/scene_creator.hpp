#ifndef UTIL_SCENE_CREATOR_HPP
#define UTIL_SCENE_CREATOR_HPP

// Std includes
#include <vector>

// Local includes
#include <lib/m3d.hpp>
#include <math/util.hpp>
#include <geometry/sphere.hpp>
#include <geometry/triangle.hpp>
#include <geometry/quad.hpp>
#include <material/material.hpp>

namespace util {

namespace sceneCreator {

// Utility

template <typename T>
std::vector<T> getRange(const std::vector<T>& parent, m3d::int32 b, m3d::int32 e) {
    b = math::clamp(b, 0, parent.size() - 1);
    e = math::clamp(e, b, parent.size() - 1);
    std::vector<T> r;
    for (m3d::int32 i = b; i <= e; i++) {
        r.push_back(parent[i]);
    }
    return r;
}

template <typename T>
std::vector<T> concat(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> r;
    for (const T& t : a) {
        r.push_back(t);
    }
    for (const T& t : b) {
        r.push_back(t);
    }
    return r;
}


// Hittables

// Basic positions
void setBasicSphere(const m3d::vec3& center, m3d::float32 radius);
void setBasicTriangle(const m3d::vec3& a, const m3d::vec3& b, const m3d::vec3& c);
void setBasicQuad(const m3d::vec3& center, const m3d::vec3& u, const m3d::vec3& v);

// Generation
std::vector<geo::Sphere> genRandomSpheres(m3d::int32 count, const m3d::vec3& tMin, const m3d::vec3& tMax, m3d::float32 sMin, m3d::float32 sMax);
std::vector<geo::Triangle> genRandomTriangles(m3d::int32 count, const m3d::vec3& tMin, const m3d::vec3& tMax, m3d::float32 rMin, m3d::float32 rMax, const m3d::vec3& aMin, const m3d::vec3& aMax, m3d::float32 sMin, m3d::float32 sMax);
std::vector<geo::Quad> genRandomQuads(m3d::int32 count, const m3d::vec3& tMin, const m3d::vec3& tMax, m3d::float32 rMin, m3d::float32 rMax, const m3d::vec3& aMin, const m3d::vec3& aMax, m3d::float32 sMin, m3d::float32 sMax);


// Materials

// Color gen
std::vector<m3d::vec3> genRandomColors(m3d::int32 count, const m3d::vec3& min, const m3d::vec3& max);
std::vector<m3d::vec3> genRandomColors(m3d::int32 count);
std::vector<m3d::vec3> pickRandomColors(m3d::int32 count, const std::vector<m3d::vec3> possibleColors, const std::vector<m3d::float32> weights);
std::vector<m3d::vec3> pickRandomColors(m3d::int32 count, const std::vector<m3d::vec3> possibleColors);

// Param gen
std::vector<m3d::float32> genRandomParams(m3d::int32 count, const m3d::float32& min, const m3d::float32& max);
std::vector<m3d::float32> genRandomParams(mat::MaterialType type, m3d::int32 count);
std::vector<m3d::float32> pickRandomParams(m3d::int32 count, const std::vector<m3d::float32> possibleParams, const std::vector<m3d::float32> weights);
std::vector<m3d::float32> pickRandomParams(m3d::int32 count, const std::vector<m3d::float32> possibleParams);

// Material creation
std::vector<mat::Material> createMaterialBatch(const mat::MaterialType& materialType, const std::vector<m3d::vec3>& colors, const std::vector<m3d::float32>& params);

} // namespace sceneCreator

} // namespace util

#endif // UTIL_SCENE_CREATOR_HPP
