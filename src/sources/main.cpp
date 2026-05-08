// Std includes
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

// Local includes
#include "image.hpp"
#include "m3d.hpp"
#include "optics.hpp"
#include "geometry.hpp"

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600
#define VFOV 25.0
#define SUPERSAMPLES 100
#define DEPTH 50

#define DIFFUSE 0x1
#define METAL 0x2
#define DIELECTRIC 0x3

using namespace m3d;

struct ScatterResult {
    Ray ray;
    vec3 color;
    bool scattered;

    ScatterResult() = default;
    ScatterResult(const Ray& ray, const vec3& color, bool scattered) : ray(ray), color(color), scattered(scattered) {}
};

struct Material {
    int32 type;
    vec3 color;
    float32 param;

    Material() = default;
    Material(int32 type, const vec3& color, float32 param) : type(type), color(color), param(param) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const {
        switch (type) {
        case DIFFUSE: {
            return ScatterResult(Ray(hp.p, diffuse(hp.normal)), color, true);
        }

        case METAL: {
            return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal) + randomUV() * param), color, true);
        }

        case DIELECTRIC: {
            return ScatterResult(
                Ray(hp.p, refract(
                    ray.dir,
                    hp.normal,
                    (hp.exit) ? param : OPTICS_AIR_REF_IDX,
                    (hp.exit) ? OPTICS_AIR_REF_IDX : param
                )),
                color,
                true
            );
        }

        default:
            return ScatterResult();
        }
    }
};

struct Object {
    Hittable* h;
    Material* m;

    Object() : h(nullptr), m(nullptr) {}
    Object(Hittable* h, Material* m) : h(h), m(m) {}

    bool hit(const Ray& ray, Hitpoint& hp, float32 minT, float32 maxT) const {
        return h->hit(ray, hp, minT, maxT);
    }
};

struct Scene {
    std::vector<Object> objects;

    Scene() = default;

    void add(const Object& obj) {
        objects.push_back(obj);
    }

    Material* hit(const Ray& ray, Hitpoint& hp) const {
        Material* mat = nullptr;
        float32 closestT = std::numeric_limits<float32>::max();
        for (const auto& obj : objects) {
            if (obj.hit(ray, hp, 0.001, closestT)) {
                mat = obj.m;
                closestT = hp.t;
            }
        }
        return mat;
    }
};

vec3 skyColor() {
    return vec3(0.8f);
}

vec3 raytrace(const Scene& scene, const Ray& ray, int32 maxDepth) {
    Ray r = ray;
    Hitpoint h;
    Material* m;
    vec3 color = vec3(1.0f);
    for (int32 i = 0; i < maxDepth; i++) {
        if ((m = scene.hit(r, h))) {
            ScatterResult res = m->scatter(r, h);
            if (res.scattered) {
                color *= res.color;
                r = res.ray;
            } else {
                return vec3();
            }
        } else {
            return color * skyColor();
        }
    }
    return vec3();
}

Sphere A(vec3(0.0f, 0.5f, 0.0f), 0.5f);
Quad B(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -4.0f), vec3(-4.0f, 0.0f, 0.0f));

Material mA(METAL, vec3(0.8f, 0.8f, 0.8f), 0.0f);
Material mB(DIFFUSE, vec3(0.3f, 0.9f, 0.0f), 0.0f);

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

    Scene scene;
    scene.add(Object(&A, &mA));
    scene.add(Object(&B, &mB));

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
