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
        return ScatterResult(Ray(hp.p, diffuse(hp.normal)), color, true);
    }
};

struct Shiny : public Material {
    m3d::vec3 color;
    float32 fuzz;

    Shiny(m3d::vec3 color, float32 fuzz) : color(color), fuzz(fuzz) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const override {
        return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal) + randomUV() * fuzz), color, true);
    }
};

struct Dielectric : public Material {
    m3d::vec3 color;
    float32 refIdx;

    Dielectric(m3d::vec3 color, float32 refIdx) : color(color), refIdx(refIdx) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const override {
        m3d::vec3 n = hp.normal;
        m3d::float32 n1 = OPTICS_AIR_REF_IDX;
        m3d::float32 n2 = refIdx;
        if (m3d::dot(ray.dir, n) > 0) {
            n = -n;
            n1 = refIdx;
            n2 = OPTICS_AIR_REF_IDX;
        }

        float32 cos = dot(-ray.dir, n);
        float32 sin = std::sqrt(1.0f - cos * cos);
        if (sin * n1 / n2 > 1.0f || reflectance(cos, n1, n2) > randomUnit()) {
            return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal)), color, true);
        }

        return ScatterResult(Ray(hp.p, refract(ray.dir, n, n1, n2)), color, true);
    }
};

#endif // MATERIALS_HPP
