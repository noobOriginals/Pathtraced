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

// Local includes
#include "types.h"
#include "m3d.hpp"
#include "geometry.hpp"
#include "render.hpp"

using namespace m3d;

Sphere sphere(vec3(2.0, 0.0, -9.0), 0.5);
Triangle triangle(vec3(0.0, 0.4330127, 0.0), vec3(-0.5, -0.4330127, 0.0), vec3(0.5, -0.4330127, 0.0));
Quad quad(vec3(0.0, -0.5, 0.0), vec3(0.0, -1.5, -4.0), vec3(-4.0, 0.0, 0.0));

Material mat(vec3(0.3f, 0.6f, 0.3f), 1.0f);

vec3 raytrace(const Ray& ray) {
    Hitpoint hp;
    vec3 color;
    if (triangle.hitRay(ray, &hp)) {
        vec3 p = ray.at(hp.t);
        float32 u, v, w;
        vec3 ab = triangle.getAB();
        vec3 ac = triangle.getAC();
        float32 area = len(cross(ab, ac));
        w = len(cross(p - triangle.getA(), ab)) / area;
        v = len(cross(p - triangle.getA(), ac)) / area;
        u = 1.0 - v - w;
        color = vec3(u, v, w);
    } else if (quad.hitRay(ray, &hp)) {
        color = mat.color * raytrace(mat.scatter(ray, hp));
    } else {
        color = vec3(0.2, 0.2, 0.2);
    }
    return color;
}

void renderRotations(Render& render, const std::vector<float64> rotations) {
    vec3 camPos(0, 4, 8);

    int32 frame = 0;
    for (auto& x : rotations) {
        render.setCameraPosAndLookat(vec3(rotate(degToRad(x), vec3(0, 1, 0)) * vec4(camPos, 1.0)), vec3(0.0, 0.0, 0.0));
        render.begin();
        while (!render.isDone()) {}
        render.save("frame" + std::to_string(frame) + ".bmp");
        frame++;
    }
}

int main() {
    Render render(800, 600, 30.0f);
    render.setRaytraceCallback(raytrace);
    render.setCameraPosAndLookat(vec3(0.0, 0.0, 12.0), vec3(0.0, 0.0, 0.0));
    render.setSupersamples(4, 4);
    render.enableSupersamling();

    std::vector<float64> rot;
    // rot.push_back(-30);
    // rot.push_back(-25);
    // rot.push_back(-20);
    // rot.push_back(-15);
    // rot.push_back(-10);
    // rot.push_back(-5);
    // rot.push_back(0);
    // rot.push_back(5);
    // rot.push_back(10);
    // rot.push_back(15);
    // rot.push_back(20);
    rot.push_back(25);
    // rot.push_back(30);

    renderRotations(render, rot);
    return 0;
}
