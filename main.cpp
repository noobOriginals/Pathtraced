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
    int32 samplesX = 4;
    int32 samplesY = 4;

    Image img(width, height);
    Pixel* pixels = img.getPixles(nullptr);

    Viewport viewport(width, height, degToRad(60.0f));
    Camera camera(Vec3(0.0, 0.0, -0.0), Vec3(0.0, 0.0, -1.0), viewport);

    Sphere sphere(Vec3(2.0, 0.0, -9.0), 0.5);

    Vec3 A(0.0, 0.4330127, -4.0);
    Vec3 B(-0.5, -0.4330127, -4.0);
    Vec3 C(0.5, -0.4330127, -4.0);
    Triangle triangle(B, C, A);

    Quad quad(Vec3(0.0, 0.5, -9.0), Vec3(0.0, 0.0, -10.0), Vec3(-10.0, 0.0, 0.0));
    std::cout << quad.getA() << "\n";
    std::cout << quad.getB() << "\n";
    std::cout << quad.getC() << "\n";
    std::cout << quad.getD() << "\n";

    for (int32 y = 0; y < height; y++) {
        for (int32 x = 0; x < width; x++) {
            Vec3 avgColor;
            Vec3 supersampleDelta = camera.getPixelDelta() / Vec3(samplesX + 1, samplesY + 1, 1.0);
            Vec3 supersampleOrigin = camera.getPixel(x, y) - camera.getPixelDelta() * 0.5 + supersampleDelta;
            for (int32 sy = 0; sy < samplesY; sy++) {
                for (int32 sx = 0; sx < samplesX; sx++) {
                    Vec3 pixel = supersampleOrigin + supersampleDelta * Vec3(sx, sy, 0.0);
                    Ray ray = Ray(camera.getPos(), normalize(pixel - camera.getPos()));
                    Hitpoint hp;
                    Vec3 color;
                    if (triangle.hitRay(ray, &hp) && false) {
                        Vec3 p = ray.at(hp.t);
                        float32 u, v, w;
                        Vec3 ab = triangle.getB() - triangle.getA();
                        Vec3 ac = triangle.getC() - triangle.getA();
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
                    avgColor += color;
                }
            }
            avgColor /= samplesX * samplesY;
            pixels[y * width + x] = Pixel(avgColor);
        }
    }

    img.save("render.bmp");
    return 0;
}
