// Std includes
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

// Local includes
#include <lib/m3d.hpp>
#include <math/util.hpp>
#include <math/ray.hpp>
#include <math/hitpoint.hpp>
#include <material/scatter_result.hpp>
#include <material/material.hpp>
#include <scene/scene.hpp>
#include <util/render.hpp>
#include <util/scene_creator.hpp>

using namespace m3d;
using namespace math;

int32 pickOneOfN(int32 n) {
    return (int32) (n * randomUnit());
}

scene::Scene scn;

geo::Quad ground = geo::Quad(vec3(0), vec3(0, 0, -10), vec3(-10, 0, 0));
mat::Material groundMat(mat::DIFFUSE, vec3(0.329, 0.329, 0.329), 0.0);

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5 * (ray.dir.y + 1.0);
    return (1.0 - a) * vec3(1.0) + a * vec3(0.5, 0.7, 1);
}

vec3 raytrace(const Ray& ray, int32 maxDepth) {
    Ray r = ray;
    Hitpoint h;
    mat::Material* m;
    vec3 color = vec3(1.0f);
    for (int32 i = 0; i < maxDepth; i++) {
        if ((m = scn.getClosestHit(r, h))) {
            mat::ScatterResult res = m->scatter(r, h);
            if (res.scattered) {
                color *= res.color;
                r = res.ray;
            } else {
                return vec3();
            }
        } else {
            return color * skyColor(r);
        }
    }
    return vec3();
}

int main() {
    util::sceneCreator::setBasicSphere(vec3(0, 0.5, 0), 0.5);
    util::sceneCreator::setBasicTriangle(vec3(-0.5, 0, 0), vec3(5, 0, 0), vec3(0, 0.866, 0));
    util::sceneCreator::setBasicQuad(vec3(0, 0.5, 0), vec3(-1, 0, 0), vec3(0, -1, 0));

    auto spheres = util::sceneCreator::genRandomSpheres(5, vec3(-1.5, 0,-1.5), vec3(3), 1, 2);
    auto triangles = util::sceneCreator::genRandomTriangles(5, vec3(-3, 1, -3), vec3(3), -180, 180, vec3(0, 1, 0), vec3(0, 0, 1), 1, 2);
    auto quads = util::sceneCreator::genRandomQuads(5, vec3(-3, 1, -3), vec3(3), -180, 180, vec3(0, 1, 0), vec3(0, 0, 1), 1, 2);

    auto colors = util::sceneCreator::genRandomColors(6, vec3(0, 0.29, 0.561), vec3(0.514, 0.769, 1));
    auto glassColors = util::sceneCreator::genRandomColors(3, vec3(0.749, 0.812, 0.871), vec3(1));

    auto metalParams = util::sceneCreator::pickRandomParams(3, {0, 0.1, 0.2});
    auto glassParams = util::sceneCreator::pickRandomParams(3, {1.33, 1.5, 2.4});

    auto diffuseMaterials = util::sceneCreator::createMaterialBatch(mat::DIFFUSE, util::sceneCreator::getRange(colors, 0, 2), {0, 0, 0});
    auto metalMaterials = util::sceneCreator::createMaterialBatch(mat::METAL, util::sceneCreator::getRange(colors, 3, 5), metalParams);
    auto glassMaterials = util::sceneCreator::createMaterialBatch(mat::DIELECTRIC, util::sceneCreator::getRange(colors, 3, 5), glassParams);

    auto materials = util::sceneCreator::concat(util::sceneCreator::concat(diffuseMaterials, metalMaterials), glassMaterials);

    for (geo::Sphere& h : spheres) {
        scn.add(scene::Object(&h, &materials[math::pickOneOfN(materials.size() - 1)]));
    }
    // for (geo::Triangle& h : triangles) {
    //     scn.add(scene::Object(&h, &materials[math::pickOneOfN(materials.size() - 1)]));
    // }
    // for (geo::Quad& h : quads) {
    //     scn.add(scene::Object(&h, &materials[math::pickOneOfN(materials.size() - 1)]));
    // }

    scn.add(scene::Object(&ground, &groundMat));

    scn.save("random_scene.scn");

    util::RenderParameters renderParameters;

    renderParameters.screenWidth = 1920;
    renderParameters.screenHeight = 1080;
    renderParameters.vfov = 34.0f;

    renderParameters.worldUp = vec3(0, 1, 0);
    renderParameters.cameraPos = vec3(-9.0f, 7.5f, 9.0f);
    renderParameters.cameraLookAt = vec3(0.0f, 0.5f, 0.0f);

    renderParameters.samplesPerPixel = 10;
    renderParameters.maxBounces = 50;

    renderParameters.enableSupersampling = true;
    renderParameters.enableGammaCorrection = false;
    renderParameters.enableMultiThreading = true;

    renderParameters.raytraceCallback = raytrace;

    util::Render render(renderParameters);
    render.render();
    render.save("render.bmp");

    return 0;
}
