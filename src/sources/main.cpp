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
#ifdef __APPLE__
#include <util/metal_render.hpp>
#endif

using namespace m3d;
using namespace math;
using namespace util::sceneCreator;

scene::Scene scn;

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5f * (ray.dir.y + 1.0f);
    return (1.0f - a) * vec3(1.0f) + a * vec3(0.5f, 0.7f, 1.0f);
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
    // Jittered grid of spheres — procedural layout with random perturbation per cell
    SphereTemplate tmpl { vec3(0, 0.4f, 0), 0.4f };
    GridParams grid { vec3(-4.0f, 0, -4.0f), vec3(2.0f, 0, 0), vec3(0, 0, 2.0f), 5, 5 };
    SphereJitter jitter { vec3(0.5f, 0, 0.5f), 0.1f };

    auto spheres   = genJitteredGridSpheres(tmpl, grid, jitter);
    auto materials = createMixedMaterialBatch((int32)spheres.size(), {
        { mat::DIFFUSE,    5.0f, vec3(0.05f, 0.2f, 0.4f),  vec3(0.5f, 0.8f, 1.0f),  0.0f, 0.0f },
        { mat::METAL,      3.0f, vec3(0.5f,  0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f),  0.0f, 0.3f },
        { mat::DIELECTRIC, 2.0f, vec3(0.9f,  0.9f, 0.9f),  vec3(1.0f, 1.0f, 1.0f),  1.3f, 1.7f },
    });

    populateScene(scn, spheres, materials);

    // Ground quad — owned by scene after populateScene call
    auto ground = std::vector<geo::Quad>{ geo::Quad(vec3(0), vec3(0, 0, -15), vec3(-15, 0, 0)) };
    auto groundMat = std::vector<mat::Material>{ mat::Material(mat::DIFFUSE, vec3(0.529f, 0.529f, 0.529f), 0.0f) };
    populateScene(scn, ground, groundMat);

    scn.save("random_scene.scn");

    util::RenderParameters renderParameters;

    renderParameters.screenWidth = 6144;
    renderParameters.screenHeight = 3456;
    renderParameters.vfov = 34.0f;

    renderParameters.worldUp = vec3(0, 1, 0);
    renderParameters.cameraPos = vec3(0.0f, 6.0f, 13.0f);
    renderParameters.cameraLookAt = vec3(0.0f, 0.5f, 0.0f);

    renderParameters.samplesPerPixel = 1000;
    renderParameters.maxBounces = 500;

    renderParameters.enableSupersampling = true;
    renderParameters.enableGammaCorrection = true;
    renderParameters.enableMultiThreading = true;

    renderParameters.raytraceCallback = raytrace;

#ifdef __APPLE__
    util::MetalRenderer render(scn, renderParameters);
    render.render();
    render.save("render.png");
#else
    util::Render render(renderParameters);
    render.render();
    render.save("render.png");
#endif

    return 0;
}
