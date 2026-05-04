#ifndef MATERIALS_HPP
#define MATERIALS_HPP

// Local includes
#include "m3d.hpp"
#include "geometry.hpp"
#include "optics.hpp"

struct ScatterResult {
    Ray ray;
    m3d::vec3 color;
    bool scattered;

    ScatterResult() = default;
    ScatterResult(Ray ray, m3d::vec3 color, bool scattered) : ray(ray), color(color), scattered(scattered) {}
};

struct Material {
    virtual ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const = 0;
};

struct Diffuse : public Material {
    m3d::vec3 color;

    Diffuse(m3d::vec3 color) : color(color) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const override {
        return ScatterResult(Ray(ray.at(hp.t), diffuse(ray.dir, hp.normal)), color, true);
    }
};

struct Shiny : public Material {
    m3d::vec3 color;
    float32 fuzz;

    Shiny(m3d::vec3 color, float32 fuzz) : color(color), fuzz(fuzz) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const override {
        m3d::vec3 dir = reflect(ray.dir, hp.normal);
        dir += randomUV() * fuzz;
        return ScatterResult(Ray(ray.at(hp.t), dir), color, true);
    }
};

struct Dielectric : public Material {
    m3d::vec3 color;
    float32 refIdx;

    Dielectric(m3d::vec3 color, float32 refIdx) : color(color), refIdx(refIdx) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const override {
        return ScatterResult(Ray(ray.at(hp.t), refract(ray.dir, hp.normal, refIdx)), color, true);
    }
};

#endif // MATERIALS_HPP
