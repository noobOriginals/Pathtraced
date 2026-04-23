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
#include "util.hpp"
#include "math.hpp"
#include "geometry.hpp"
#include "camera.hpp"
#include "image.hpp"

int main() {
    int32 width = 800;
    int32 height = 600;

    Image img(width, height);
    Pixel* pixels = img.getPixles(nullptr);

    Viewport viewport(width, height, degToRad(60.0f));
    Camera camera(Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -2.0), viewport);

    Sphere sphere(Vec3(2.0, 0.0, -9.0), 0.5);

    Vec3 A(0.0, 0.5, -4.0);
    Vec3 B(-0.5, -0.5, -4.0);
    Vec3 C(0.5, -0.5, -4.0);
    Triangle triangle(A, B, C);

    for (int32 y = 0; y < height; y++) {
        for (int32 x = 0; x < width; x++) {
            Ray ray = Ray(camera.getPos(), camera.getPixel(x, y) - camera.getPos());
            Hitpoint hp;
            Vec3 color;
            if (triangle.hitRay(ray, &hp)) {
                color = Vec3(clamp(len(ray.at(hp.t) - triangle.getA()), 0.0, 1.0));
            } else {
                color = Vec3(0.1, 0.1, 0.1);
            }
            pixels[y * width + x] = Pixel(color);
        }
    }

    img.save("render.bmp");
    return 0;
}
