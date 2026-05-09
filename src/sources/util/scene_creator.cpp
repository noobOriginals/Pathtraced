#include <util/scene_creator.hpp>

// Local includes
#include <math/util.hpp>

using namespace m3d;

namespace util {

namespace sceneCreator {

// Hittable generation — random

std::vector<geo::Sphere> genRandomSpheres(const SphereTemplate& tmpl, int32 count, const vec3& tMin, const vec3& tMax, float32 sMin, float32 sMax) {
    std::vector<geo::Sphere> spheres;
    for (int32 i = 0; i < count; i++) {
        vec3 center = tmpl.center + math::randomVec(tMin, tMax);
        spheres.push_back(geo::Sphere(center, tmpl.radius * math::randomUnit(sMin, sMax)));
    }
    return spheres;
}

std::vector<geo::Triangle> genRandomTriangles(const TriangleTemplate& tmpl, int32 count, const vec3& tMin, const vec3& tMax, float32 rMin, float32 rMax, const vec3& aMin, const vec3& aMax, float32 sMin, float32 sMax) {
    std::vector<geo::Triangle> triangles;
    for (int32 i = 0; i < count; i++) {
        mat4 transform = translate(mat4(1.0f), math::randomVec(tMin, tMax));
        transform = rotate(transform, degToRad(math::randomUnit(rMin, rMax)), normalize(math::randomVec(aMin, aMax)));
        transform = scale(transform, vec3(math::randomUnit(sMin, sMax)));
        triangles.push_back(geo::Triangle(
            vec3(transform * vec4(tmpl.a)),
            vec3(transform * vec4(tmpl.b)),
            vec3(transform * vec4(tmpl.c))
        ));
    }
    return triangles;
}

std::vector<geo::Quad> genRandomQuads(const QuadTemplate& tmpl, int32 count, const vec3& tMin, const vec3& tMax, float32 rMin, float32 rMax, const vec3& aMin, const vec3& aMax, float32 sMin, float32 sMax) {
    std::vector<geo::Quad> quads;
    for (int32 i = 0; i < count; i++) {
        mat4 transform = rotate(mat4(1.0f), degToRad(math::randomUnit(rMin, rMax)), normalize(math::randomVec(aMin, aMax)));
        transform = scale(transform, vec3(math::randomUnit(sMin, sMax)));
        quads.push_back(geo::Quad(
            tmpl.center + math::randomVec(tMin, tMax),
            vec3(transform * vec4(tmpl.u)),
            vec3(transform * vec4(tmpl.v))
        ));
    }
    return quads;
}


// Hittable generation — grid (procedural and jittered-blend)

std::vector<geo::Sphere> genGridSpheres(const SphereTemplate& tmpl, const GridParams& grid) {
    std::vector<geo::Sphere> spheres;
    for (int32 row = 0; row < grid.rows; row++) {
        for (int32 col = 0; col < grid.cols; col++) {
            vec3 center = grid.origin + (float32)col * grid.stepX + (float32)row * grid.stepZ;
            spheres.push_back(geo::Sphere(center + tmpl.center, tmpl.radius));
        }
    }
    return spheres;
}

std::vector<geo::Sphere> genJitteredGridSpheres(const SphereTemplate& tmpl, const GridParams& grid, const SphereJitter& jitter) {
    std::vector<geo::Sphere> spheres;
    for (int32 row = 0; row < grid.rows; row++) {
        for (int32 col = 0; col < grid.cols; col++) {
            vec3 cell = grid.origin + (float32)col * grid.stepX + (float32)row * grid.stepZ;
            vec3 offset = math::randomVec(-jitter.posJitter, jitter.posJitter);
            float32 radius = tmpl.radius + math::randomUnit(-jitter.radiusJitter, jitter.radiusJitter);
            spheres.push_back(geo::Sphere(cell + tmpl.center + offset, radius));
        }
    }
    return spheres;
}


// Materials

// Color gen
std::vector<vec3> genRandomColors(int32 count, const vec3& min, const vec3& max) {
    std::vector<vec3> colors;
    for (int32 i = 0; i < count; i++) {
        colors.push_back(math::randomVec(min, max));
    }
    return colors;
}

std::vector<vec3> genRandomColors(int32 count) {
    return genRandomColors(count, 0.0f, 1.0f);
}

std::vector<vec3> pickRandomColors(int32 count, const std::vector<vec3> possibleColors, const std::vector<float32> weights) {
    std::vector<vec3> colors;
    for (int32 i = 0; i < count; i++) {
        colors.push_back(possibleColors[math::pickWeightedOneOfN(weights)]);
    }
    return colors;
}

std::vector<vec3> pickRandomColors(int32 count, const std::vector<vec3> possibleColors) {
    std::vector<vec3> colors;
    for (int32 i = 0; i < count; i++) {
        colors.push_back(possibleColors[math::pickOneOfN((int32)possibleColors.size() - 1)]);
    }
    return colors;
}

// Param gen
std::vector<float32> genRandomParams(int32 count, const float32& min, const float32& max) {
    std::vector<float32> params;
    for (int32 i = 0; i < count; i++) {
        params.push_back(math::randomUnit(min, max));
    }
    return params;
}

std::vector<float32> genRandomParams(mat::MaterialType type, int32 count) {
    return genRandomParams(count, (type == mat::METAL) ? 0.0f : 1.0f, (type == mat::METAL) ? 1.0f : 2.0f);
}

std::vector<float32> pickRandomParams(int32 count, const std::vector<float32> possibleParams, const std::vector<float32> weights) {
    std::vector<float32> params;
    for (int32 i = 0; i < count; i++) {
        params.push_back(possibleParams[math::pickWeightedOneOfN(weights)]);
    }
    return params;
}

std::vector<float32> pickRandomParams(int32 count, const std::vector<float32> possibleParams) {
    std::vector<float32> params;
    for (int32 i = 0; i < count; i++) {
        params.push_back(possibleParams[math::pickOneOfN((int32)possibleParams.size() - 1)]);
    }
    return params;
}

// Single-type batch creation
std::vector<mat::Material> createMaterialBatch(const mat::MaterialType& materialType, const std::vector<vec3>& colors, const std::vector<float32>& params) {
    std::vector<mat::Material> materials;
    for (int32 i = 0; i < (int32)colors.size() && i < (int32)params.size(); i++) {
        materials.push_back(mat::Material(materialType, colors[i], params[i]));
    }
    return materials;
}

// Mixed-type batch creation
std::vector<mat::Material> createMixedMaterialBatch(int32 count, const std::vector<MaterialSpec>& specs) {
    std::vector<float32> weights;
    for (const MaterialSpec& s : specs) weights.push_back(s.weight);

    std::vector<mat::Material> materials;
    for (int32 i = 0; i < count; i++) {
        const MaterialSpec& s = specs[math::pickWeightedOneOfN(weights)];
        vec3    color = math::randomVec(s.colorMin, s.colorMax);
        float32 param = math::randomUnit(s.paramMin, s.paramMax);
        materials.push_back(mat::Material(s.type, color, param));
    }
    return materials;
}


// Scene population

void populateScene(scene::Scene& scene, const std::vector<geo::Sphere>& spheres, const std::vector<mat::Material>& materials) {
    for (int32 i = 0; i < (int32)spheres.size(); i++) {
        scene.add(scene::Object(
            spheres[i].clone(),
            new mat::Material(materials[i % (int32)materials.size()])
        ));
    }
}

void populateScene(scene::Scene& scene, const std::vector<geo::Triangle>& triangles, const std::vector<mat::Material>& materials) {
    for (int32 i = 0; i < (int32)triangles.size(); i++) {
        scene.add(scene::Object(
            triangles[i].clone(),
            new mat::Material(materials[i % (int32)materials.size()])
        ));
    }
}

void populateScene(scene::Scene& scene, const std::vector<geo::Quad>& quads, const std::vector<mat::Material>& materials) {
    for (int32 i = 0; i < (int32)quads.size(); i++) {
        scene.add(scene::Object(
            quads[i].clone(),
            new mat::Material(materials[i % (int32)materials.size()])
        ));
    }
}

} // namespace sceneCreator

} // namespace util
