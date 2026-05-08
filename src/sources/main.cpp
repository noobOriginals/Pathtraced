// Std includes
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

// Local includes
#include <lib/m3d.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>
#include <geometry/sphere.hpp>
#include <geometry/quad.hpp>
#include <material/scatter_result.hpp>
#include <material/material.hpp>
#include <scene/object.hpp>
#include <scene/scene.hpp>
#include <render.hpp>

using namespace m3d;
using namespace geo;
using namespace mat;
using namespace scene;

Scene scn("default_scene.scn");

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5 * (ray.dir.y + 1.0);
    return (1.0 - a) * vec3(1.0) + a * vec3(0.5, 0.7, 1);
}

vec3 raytrace(const Ray& ray, int32 maxDepth) {
    Ray r = ray;
    Hitpoint h;
    Material* m;
    vec3 color = vec3(1.0f);
    for (int32 i = 0; i < maxDepth; i++) {
        if ((m = scn.getClosestHit(r, h))) {
            ScatterResult res = m->scatter(r, h);
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
    RenderParameters renderParameters;

    renderParameters.screenWidth = 2560;
    renderParameters.screenHeight = 1440;
    renderParameters.vfov = 25.0f;

    renderParameters.worldUp = vec3(0, 1, 0);
    renderParameters.cameraPos = vec3(0.0f, 1.5f, 4.0f);
    renderParameters.cameraLookAt = vec3(0.0f, 0.5f, 0.0f);

    renderParameters.samplesPerPixel = 100;
    renderParameters.maxBounces = 100;

    renderParameters.enableSupersampling = true;
    renderParameters.enableGammaCorrection = true;
    renderParameters.enableMultiThreading = true;

    renderParameters.raytraceCallback = raytrace;

    Render render(renderParameters);
    render.render();
    render.save("render.bmp");
    return 0;
}
