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
#include <scene/scene.hpp>

namespace util {

namespace sceneCreator {

// Utility

template <typename T>
std::vector<T> getRange(const std::vector<T>& parent, m3d::int32 b, m3d::int32 e) {
    b = math::clamp(b, 0, (m3d::int32)parent.size() - 1);
    e = math::clamp(e, b, (m3d::int32)parent.size() - 1);
    std::vector<T> r;
    for (m3d::int32 i = b; i <= e; i++) {
        r.push_back(parent[i]);
    }
    return r;
}

template <typename T>
std::vector<T> concat(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> r;
    for (const T& t : a) r.push_back(t);
    for (const T& t : b) r.push_back(t);
    return r;
}


// Shape templates — replace the old setBasic* global state

struct SphereTemplate   { m3d::vec3 center; m3d::float32 radius; };
struct TriangleTemplate { m3d::vec3 a, b, c; };
struct QuadTemplate     { m3d::vec3 center, u, v; };


// Grid / jitter config

struct GridParams {
    m3d::vec3  origin;  // world position of cell (0, 0)
    m3d::vec3  stepX;   // displacement per column
    m3d::vec3  stepZ;   // displacement per row
    m3d::int32 cols;
    m3d::int32 rows;
};

struct SphereJitter {
    m3d::vec3    posJitter;     // random offset applied ± per axis
    m3d::float32 radiusJitter;  // random delta applied ± to template radius
};


// Hittable generation — random

std::vector<geo::Sphere>   genRandomSpheres(const SphereTemplate& tmpl, m3d::int32 count, const m3d::vec3& tMin, const m3d::vec3& tMax, m3d::float32 sMin, m3d::float32 sMax);
std::vector<geo::Triangle> genRandomTriangles(const TriangleTemplate& tmpl, m3d::int32 count, const m3d::vec3& tMin, const m3d::vec3& tMax, m3d::float32 rMin, m3d::float32 rMax, const m3d::vec3& aMin, const m3d::vec3& aMax, m3d::float32 sMin, m3d::float32 sMax);
std::vector<geo::Quad>     genRandomQuads(const QuadTemplate& tmpl, m3d::int32 count, const m3d::vec3& tMin, const m3d::vec3& tMax, m3d::float32 rMin, m3d::float32 rMax, const m3d::vec3& aMin, const m3d::vec3& aMax, m3d::float32 sMin, m3d::float32 sMax);

// Hittable generation — procedural (grid)

std::vector<geo::Sphere> genGridSpheres(const SphereTemplate& tmpl, const GridParams& grid);
std::vector<geo::Sphere> genJitteredGridSpheres(const SphereTemplate& tmpl, const GridParams& grid, const SphereJitter& jitter);


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

// Single-type batch creation (existing)
std::vector<mat::Material> createMaterialBatch(const mat::MaterialType& materialType, const std::vector<m3d::vec3>& colors, const std::vector<m3d::float32>& params);

// Mixed-type batch creation
struct MaterialSpec {
    mat::MaterialType type;
    m3d::float32      weight;
    m3d::vec3         colorMin, colorMax;
    m3d::float32      paramMin, paramMax;
};

std::vector<mat::Material> createMixedMaterialBatch(m3d::int32 count, const std::vector<MaterialSpec>& specs);


// Scene population — clones geometry and heap-allocates materials; scene takes ownership

void populateScene(scene::Scene& scene, const std::vector<geo::Sphere>&   spheres,   const std::vector<mat::Material>& materials);
void populateScene(scene::Scene& scene, const std::vector<geo::Triangle>& triangles, const std::vector<mat::Material>& materials);
void populateScene(scene::Scene& scene, const std::vector<geo::Quad>&     quads,     const std::vector<mat::Material>& materials);

} // namespace sceneCreator

} // namespace util

#endif // UTIL_SCENE_CREATOR_HPP
