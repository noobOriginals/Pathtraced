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
#include "m3d.hpp"
#include "geometry.hpp"
#include "render.hpp"
#include "materials.hpp"
#include "scene.hpp"

using namespace m3d;

// Quad ground(vec3(0.0), vec3(0.0, 0.0, -7.0), vec3(-7.0, 0.0, 0.0));
Sphere ground(vec3(0.0, -100.0, 0.0), 100.0);
Sphere A(vec3(0.0, 0.5, -0.2), 0.5);
Sphere B(vec3(-1.0, 0.5, 0.0), 0.5);
Sphere nestedB(vec3(-1.0, 0.5, 0.0), 0.4);
Sphere C(vec3(1.0, 0.5, 0.0), 0.5);

Material matG(LAMBERTIAN, vec3(0.8, 0.8, 0.0));
Material matA(LAMBERTIAN, vec3(0.1, 0.2, 0.5));
Material matB(DIELECTRIC, vec3(1.0), 1.5);
Material matNestedB(DIELECTRIC, vec3(1.0), 1.0 / 1.5);
Material matC(METAL, vec3(0.8, 0.6, 0.2), 0.3);

int main() {
    Scene scene(900, 500, 25.0f);
    scene.getRender().setSupersamples(15, 15);
    scene.getRender().enableSupersamling();
    scene.getRender().enableGammaCorrection();
    scene.getRender().enableMultithreading();
    scene.getRender().setMaxDepth(100);

    scene.add(Object(&ground, &matG));
    scene.add(Object(&A, &matA));
    scene.add(Object(&B, &matB));
    scene.add(Object(&nestedB, &matNestedB));
    scene.add(Object(&C, &matC));

    scene.getRender().setCameraPosAndLookat(vec3(0.0, 1.5, 4.0), vec3(0.0, 0.5, 0.0));

    scene.saveScene("scene1.sc");

    scene.renderScene();
    scene.saveRender("render.bmp");
    return 0;
}
