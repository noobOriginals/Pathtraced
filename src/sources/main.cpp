// Std includes
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

// Local includes
#include <lib/image.hpp>
#include <lib/m3d.hpp>
#include <util.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>
#include <geometry/sphere.hpp>
#include <geometry/quad.hpp>
#include <material/scatter_result.hpp>
#include <material/material.hpp>
#include <scene/object.hpp>
#include <scene/scene.hpp>

#define IMAGE_WIDTH 900
#define IMAGE_HEIGHT 500
#define VFOV 25.0
#define SUPERSAMPLES 50
#define DEPTH 50

using namespace m3d;
using namespace geo;
using namespace mat;
using namespace scene;

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5 * (ray.dir.y + 1.0);
    return (1.0 - a) * vec3(1.0) + a * vec3(0.5, 0.7, 1);
}

vec3 raytrace(const Scene& scene, const Ray& ray, int32 maxDepth) {
    Ray r = ray;
    Hitpoint h;
    Material* m;
    vec3 color = vec3(1.0f);
    for (int32 i = 0; i < maxDepth; i++) {
        if ((m = scene.getClosestHit(r, h))) {
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
// Sphere B(vec3(0.0f, -100.0f, 0.0f), 100.0f);
Quad B(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -4.0f), vec3(-4.0f, 0.0f, 0.0f));
Sphere C(vec3(-1.0f, 0.5f, 0.0f), 0.5f);
Sphere D(vec3(-1.0f, 0.5f, 0.0f), 0.4f);
Sphere E(vec3(1.0f, 0.5f, 0.0f), 0.5f);

Material mA(MaterialType::DIFFUSE, vec3(0.1f, 0.2f, 0.5f), 0.0f);
Material mB(MaterialType::DIFFUSE, vec3(0.8f, 0.8f, 0.0f), 0.0f);
Material mC(MaterialType::DIELECTRIC, vec3(1.0f, 1.0f, 1.0f), 1.5f);
Material mD(MaterialType::DIELECTRIC, vec3(1.0f, 1.0f, 1.0f), 0.6666667f);
Material mE(MaterialType::METAL, vec3(0.8f, 0.6f, 0.2f), 0.3f);

int main() {
    vec3 worldUp(0, 1, 0);

    vec3 pos(0.0f, 1.5f, 4.0f);
    vec3 lookat(0.0f, 0.5f, 0.0f);

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

    Scene scene;
    scene.add(Object(&A, &mA));
    scene.add(Object(&B, &mB));
    scene.add(Object(&C, &mC));
    scene.add(Object(&D, &mD));
    scene.add(Object(&E, &mE));

    for (int32 y = 0; y < IMAGE_HEIGHT; y++) {
        for (int32 x = 0; x < IMAGE_WIDTH; x++) {
            vec3 pixel = pixelOrigin + pixelDeltaX * x + pixelDeltaY * y;
            vec3 color(0);
            for (int32 s = 0; s < SUPERSAMPLES; s++) {
                vec3 jitter = (pixelDeltaX + pixelDeltaY) * (randomUnit() - 0.5f);
                color += raytrace(scene, Ray(pos, normalize(pixel + jitter - pos)), DEPTH);
            }
            color /= SUPERSAMPLES;
            img.set(y * IMAGE_WIDTH + x, Pixel(color));
        }
    }

    img.save("render.bmp");
    return 0;
}
