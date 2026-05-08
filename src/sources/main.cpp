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

#define IMAGE_WIDTH 2560
#define IMAGE_HEIGHT 1440
#define VFOV 25.0
#define SUPERSAMPLES 10
#define DEPTH 100

using namespace m3d;
using namespace geo;
using namespace mat;
using namespace scene;

Scene scn;

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

Sphere A(vec3(0.0f, 0.5f, -0.2f), 0.5f);
Quad B(vec3(0.0f, -0.01f, 0.0f), vec3(0.0f, 0.0f, -4.0f), vec3(-4.0f, 0.0f, 0.0f));
Sphere C(vec3(-1.0f, 0.5f, 0.0f), 0.5f);
Sphere D(vec3(-1.0f, 0.5f, 0.0f), 0.4f);
Sphere E(vec3(1.0f, 0.5f, 0.0f), 0.5f);

Material mA(DIFFUSE, vec3(0.1f, 0.2f, 0.5f), 0.0f);
Material mB(DIFFUSE, vec3(0.8f, 0.8f, 0.0f), 0.0f);
Material mC(DIELECTRIC, vec3(1.0f, 1.0f, 1.0f), 1.5f);
Material mD(DIELECTRIC, vec3(1.0f, 1.0f, 1.0f), 0.6666667f);
Material mE(METAL, vec3(0.8f, 0.6f, 0.2f), 0.3f);

int main() {
    scn.add(Object(&A, &mA));
    scn.add(Object(&B, &mB));
    scn.add(Object(&C, &mC));
    scn.add(Object(&D, &mD));
    scn.add(Object(&E, &mE));
    scn.save("default_scene.scn");

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
