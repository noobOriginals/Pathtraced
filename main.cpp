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

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5 * (ray.dir.y + 1.0);
    return (1.0 - a) * vec3(1.0) + a * vec3(0.5, 0.7, 1);
}

// Quad ground(vec3(0.0), vec3(0.0, 0.0, -7.0), vec3(-7.0, 0.0, 0.0));
Sphere ground(vec3(0.0, -100.0, 0.0), 100.0);
Sphere A(vec3(0.0, 0.5, -0.2), 0.5);
Sphere B(vec3(-1.0, 0.5, 0.0), 0.5);
Sphere nestedB(vec3(-1.0, 0.5, 0.0), 0.4);
Sphere C(vec3(1.0, 0.5, 0.0), 0.5);
Diffuse matG(vec3(0.8, 0.8, 0.0));
Diffuse matA(vec3(0.1, 0.2, 0.5));
Dielectric matB(vec3(1.0), 1.5);
Dielectric matNestedB(vec3(1.0), 1.0 / 1.5);
Shiny matC(vec3(0.8, 0.6, 0.2), 1.0);

Scene scene;

vec3 raytrace(const Ray& ray, int32 depth) {
    if (depth < 1) {
        return vec3(0.0f);
    }
    vec3 color = skyColor(ray);
    Hitpoint hp;
    Material* mat;
    if ((mat = traceScene(scene, ray, &hp))) {
        ScatterResult r = mat->scatter(ray, hp);
        color = r.color;
        if (r.scattered) {
            color *= raytrace(r.ray, depth - 1);
        } else {
            color = vec3(0.0f);
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
    scene.push_back(Body(&ground, &matG));
    scene.push_back(Body(&A, &matA));
    scene.push_back(Body(&B, &matB));
    scene.push_back(Body(&nestedB, &matNestedB));
    scene.push_back(Body(&C, &matC));

    Render render(900, 500, 25.0f);
    render.setRaytraceCallback(raytrace);
    render.setSupersamples(15, 15);
    render.enableSupersamling();
    render.enableGammaCorrection();
    render.enableMultithreading();
    render.setMaxDepth(100);

    render.setCameraPosAndLookat(vec3(0.0, 0.5, 4.0), vec3(0.0, 0.5, 0.0));

    render.render();
    render.save("render.bmp");
    return 0;
}
