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
Triangle triangle(vec3(0.0, 0.4330127, -0.5), vec3(-0.5, -0.4330127, -0.5), vec3(0.5, -0.4330127, -0.5));
Quad quad(vec3(0.0, -0.5, -1.0), vec3(0.0, 0.0, -30.0), vec3(-5.0, 0.0, 0.0));

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
        color = vec3(1.0);
    } else {
        color = vec3(0.1, 0.1, 0.1);
    }
    return color;
}

int main() {
    Render render(800, 600, 30.0f);
    render.setRaytraceCallback(raytrace);
    render.setCameraPosAndLookat(vec3(0.0, 0.0, 12.0), vec3(0.0, 0.0, 0.0));
    render.setSupersamples(5, 5);
    render.enableSupersamling();

    render.begin();
    while (!render.isDone()) {}

    render.save("render.bmp");
    return 0;
}
