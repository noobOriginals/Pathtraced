#include <util/scene_creator.hpp>

// Local includes
#include <math/util.hpp>

using namespace m3d;

namespace util {

namespace sceneCreator {

// Hittables

vec3 sphereCenter;
float32 sphereRadius;

vec3 triangleA, triangleB, triangleC;

vec3 quadCenter, quadU, quadV;

// Basic positions
void setBasicSphere(const vec3& center, float32 radius) {
    sphereCenter = center;
    sphereRadius = radius;
}

void setBasicTriangle(const vec3& a, const vec3& b, const vec3& c) {
    triangleA = a;
    triangleB = b;
    triangleC = c;
}

void setBasicQuad(const vec3& center, const vec3& u, const vec3& v) {
    quadCenter = center;
    quadU = u;
    quadV = v;
}

// Generation
std::vector<geo::Sphere> genRandomSpheres(int32 count, const vec3& tMin, const vec3& tMax, float32 sMin, float32 sMax) {
    std::vector<geo::Sphere> spheres;
    for (int32 i = 0; i < count; i++) {
        vec3 center = sphereCenter + math::randomVec(tMin, tMax);
        spheres.push_back(geo::Sphere(center, sphereRadius * math::randomUnit(sMin, sMax)));
    }
    return spheres;
}

std::vector<geo::Triangle> genRandomTriangles(int32 count, const vec3& tMin, const vec3& tMax, float32 rMin, float32 rMax, const vec3& aMin, const vec3& aMax, float32 sMin, float32 sMax) {
    std::vector<geo::Triangle> triangles;
    for (int32 i = 0; i < count; i++) {
        mat4 transform = translate(mat4(1.0f), math::randomVec(tMin, tMax));
        transform = rotate(transform, degToRad(math::randomUnit(rMin, rMax)), normalize(math::randomVec(aMin, aMax)));
        transform = scale(transform, vec3(math::randomUnit(sMin, sMax)));
        triangles.push_back(geo::Triangle(
            vec3(transform * vec4(triangleA)),
            vec3(transform * vec4(triangleB)),
            vec3(transform * vec4(triangleC))
        ));
    }
    return triangles;
}

std::vector<geo::Quad> genRandomQuads(int32 count, const vec3& tMin, const vec3& tMax, float32 rMin, float32 rMax, const vec3& aMin, const vec3& aMax, float32 sMin, float32 sMax) {
    std::vector<geo::Quad> quads;
    for (int32 i = 0; i < count; i++) {
        mat4 transform = rotate(mat4(1.0f), degToRad(math::randomUnit(rMin, rMax)), normalize(math::randomVec(aMin, aMax)));
        transform = scale(transform, vec3(math::randomUnit(sMin, sMax)));
        quads.push_back(geo::Quad(
            quadCenter + math::randomVec(tMin, tMax),
            vec3(transform * vec4(quadU)),
            vec3(transform * vec4(quadV))
        ));
    }
    return quads;
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
        colors.push_back(possibleColors[math::pickOneOfN(possibleColors.size() - 1)]);
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
        params.push_back(possibleParams[math::pickOneOfN(possibleParams.size() - 1)]);
    }
    return params;
}

// Material creation
std::vector<mat::Material> createMaterialBatch(const mat::MaterialType& materialType, const std::vector<vec3>& colors, const std::vector<float32>& params) {
    std::vector<mat::Material> materials;
    int32 i = 0;
    for (const vec3& color: colors) {
        materials.push_back(mat::Material(materialType, color, params[i]));
        i++;
        if (i >= params.size()) {
            break;
        }
    }
    return materials;
}

} // namespace sceneCreator

} // namespace util
