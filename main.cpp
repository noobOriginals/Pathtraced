// Std includes
#include <iostream>
#include <cmath>

// Local includes
#include "image.hpp"
#include "m3d.hpp"
#include "optics.hpp"
#include "geometry.hpp"

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600
#define VFOV 25.0
#define SUPERSAMPLES 50
#define DEPTH 50

using namespace m3d;

Sphere s(vec3(0, 0, 0), 0.5);

vec3 raytrace(const Ray& ray, int32 maxDepth) {
    Hitpoint hp;
    if (s.hit(ray, hp, 0.001, 1000000)) {
        return vec3(1.0);
    }
    return vec3(0.1);
}

int main() {
    vec3 worldUp(0, 1, 0);

    vec3 pos(0, 1, 5);
    vec3 lookat(0);

    vec3 dir = normalize(lookat - pos);
    vec3 right = normalize(cross(dir, worldUp));
    vec3 up = normalize(cross(right, dir));

    float32 focal = 0.5f;
    float32 height = std::tan(degToRad(VFOV * 0.5f)) * focal;
    float32 width = height * IMAGE_WIDTH / IMAGE_HEIGHT;

    vec3 pixelDeltaX = right * (2.0f * width / IMAGE_WIDTH);
    vec3 pixelDeltaY = up * (2.0f * height / IMAGE_HEIGHT);
    vec3 pixelOrigin = pos + dir * focal - right * width - up * height + pixelDeltaX * 0.5f + pixelDeltaY * 0.5f;

    Image img(IMAGE_WIDTH, IMAGE_HEIGHT);

    for (int32 y = 0; y < IMAGE_HEIGHT; y++) {
        for (int32 x = 0; x < IMAGE_WIDTH; x++) {
            vec3 pixel = pixelOrigin + pixelDeltaX * x + pixelDeltaY * y;
            vec3 color(0);
            for (int32 s = 0; s < SUPERSAMPLES; s++) {
                vec3 jitter = (pixelDeltaX + pixelDeltaY) * (randomUnit() - 0.5f);
                color += raytrace(Ray(pos, normalize(pixel + jitter - pos)), DEPTH);
            }
            color /= SUPERSAMPLES;
            img.set(y * IMAGE_WIDTH + x, Pixel(color));
        }
    }

    img.save("render.bmp");
    return 0;
}
