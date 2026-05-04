/**
    As this is also a project that's being worked on from school, the following message is meant for
    anyone who may stumble onto this project (on the coputers at school):

    The goal of this project is to create a CPU pathtracer from scratch. Being a large project and
    containing many files, it's rather hard to import/export to/from Code::Blocks. So I kindly ask of you to take care of
    this project, in the event that you need to delete it. You could upload it to drive or anything
    like that, but please consider not rendering all of this work pointless.

    Repository of this project: https://github.com/noobOriginals/Pathtraced
 */

// Std includes
#include <iostream>
#include <vector>
#include <cstdlib>

// Local includes
#include "types.h"
#include "m3d.hpp"
#include "geometry.hpp"
#include "render.hpp"
#include "materials.hpp"
#include "scene.hpp"

using namespace m3d;

vec3 sunDir = normalize(vec3(-1.0, 10, -1.1));
vec3 skyColor(const Ray& ray) {
    float t = 0.5f * (ray.dir.y + 1.0f); // 0 = horizon, 1 = zenith

    // Base sky gradient (horizon → zenith)
    vec3 horizon = {0.85f, 0.92f, 1.00f};
    vec3 zenith = {0.10f, 0.40f, 0.90f};
    vec3 sky = horizon * (1.0f - t) + zenith * t;

    // Sun disk
    float sunAmmount = std::max(0.0f, ray.dir.dot(sunDir));
    vec3 sunColor = {1.40f, 1.20f, 0.60f}; // slightly warm white
    sky = sky + sunColor * std::pow(sunAmmount, 256.0f); // tight disk

    // Corona / glow around sun
    sky = sky + sunColor * 0.3f * std::pow(sunAmmount, 8.0f);

    return clamp(sky, 0.0, 1.0);
}

Sphere sphere(vec3(-1.0, 0.3, 0.3), 0.5);
Sphere sphereIn(vec3(-1.0, 0.3, 0.3), 0.4);
Triangle triangle(vec3(0.0, 0.4330127, 0.0), vec3(-0.5, -0.4330127, 0.0), vec3(0.5, -0.4330127, 0.0));
Quad quad1(vec3(0.0, -0.43, 0.0), vec3(0.0, -1.0, -4.0), vec3(-4.0, 0.0, 0.0));
Quad quad2(vec3(1.2, 0.45, 0.5), normalize(vec3(-0.08, 0.0, -0.2)), normalize(vec3(0.04, -1.0, 0.0)));

Diffuse matte1(vec3(1.0, 0.4, 0.3));
Dielectric glass1(vec3(0.84, 0.84, 0.84), 1.5);
Dielectric water(vec3(1.0, 1.0, 1.0), OPTICS_AIR_REF_IDX);
Diffuse matte2(vec3(0.1, 0.8, 0.1));
Shiny metal1(vec3(0.7), 0.005);

Scene scene;

vec3 raytrace(const Ray& ray, int32 depth) {
    vec3 color = skyColor(ray);
    if (depth < 1) {
        return color;
    }
    Hitpoint hp;
    Material* mat;
    if ((mat = traceScene(scene, ray, &hp))) {
        ScatterResult r = mat->scatter(ray, hp);
        color = r.color;
        if (r.scattered) {
            color *= raytrace(r.ray, depth - 1);
        }
    }
    return color;
}

void renderRotations(Render& render, const std::vector<float64> rotations) {
    vec3 camPos(0, 3, 6);

    int32 frame = 0;
    for (auto& x : rotations) {
        render.setCameraPosAndLookat(vec3(rotate(degToRad(x), vec3(0, 1, 0)) * vec4(camPos, 1.0)), vec3(0.0, 0.0, 0.0));
        render.render();
        render.save("frame" + std::to_string(frame) + ".bmp");
        frame++;
    }
}

int main() {
    scene.push_back(Body(&triangle, &matte1));
    scene.push_back(Body(&sphere, &glass1));
    // scene.push_back(Body(&sphereIn, &water));
    scene.push_back(Body(&quad2, &metal1));
    scene.push_back(Body(&quad1, &matte2));

    Render render(700, 500, 25.0f);
    render.setRaytraceCallback(raytrace);
    render.setCameraPosAndLookat(vec3(0.0, 0.0, 12.0), vec3(0.0, 0.0, 0.0));
    render.setSupersamples(20, 20);
    render.enableSupersamling();
    render.enableGammaCorrection();
    render.enableMultithreading();
    render.setMaxDepth(100);

    std::vector<float64> rot;
    // rot.push_back(-30);
    // rot.push_back(-25);
    rot.push_back(-20);
    // rot.push_back(-15);
    // rot.push_back(-10);
    // rot.push_back(-5);
    // rot.push_back(0);
    // rot.push_back(5);
    // rot.push_back(10);
    // rot.push_back(15);
    // rot.push_back(20);
    // rot.push_back(25);
    // rot.push_back(30);

    renderRotations(render, rot);
    return 0;
}
