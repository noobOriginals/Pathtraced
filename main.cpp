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
#include "math.hpp"
#include "geometry.hpp"
#include "render.hpp"

Sphere sphere(Vec3(2.0, 0.0, -9.0), 0.5);
Triangle triangle(Vec3(0.0, 0.4330127, -0.5), Vec3(-0.5, -0.4330127, -0.5), Vec3(0.5, -0.4330127, -0.5));
Quad quad(Vec3(0.0, -0.5, -1.0), Vec3(0.0, 0.0, -30.0), Vec3(-5.0, 0.0, 0.0));

Vec3 raytrace(const Ray& ray) {
    Hitpoint hp;
    Vec3 color;
    if (triangle.hitRay(ray, &hp)) {
        Vec3 p = ray.at(hp.t);
        float32 u, v, w;
        Vec3 ab = triangle.getAB();
        Vec3 ac = triangle.getAC();
        float32 area = len(cross(ab, ac));
        w = len(cross(p - triangle.getA(), ab)) / area;
        v = len(cross(p - triangle.getA(), ac)) / area;
        u = 1.0 - v - w;
        color = Vec3(u, v, w);
    } else if (quad.hitRay(ray, &hp)) {
        color = Vec3(1.0);
    } else {
        color = Vec3(0.1, 0.1, 0.1);
    }
    return color;
}

int main() {
    Render render(800, 600, 30.0f);
    render.setRaytraceCallback(raytrace);
    render.setCameraPosAndLookat(Vec3(0.0, 0.0, 12.0), Vec3(0.0, 0.0, 0.0));
    render.setSupersamples(5, 5);
    render.enableSupersamling();

    render.begin();
    while (!render.isDone()) {}

    render.save("render.bmp");
    return 0;
}
