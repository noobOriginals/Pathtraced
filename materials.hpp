#ifndef MATERIALS_HPP
#define MATERIALS_HPP

// Local includes
#include "m3d.hpp"
#include "geometry.hpp"

struct ScatterResult {
    Ray ray;
    m3d::vec3 color;
    bool scattered;

    ScatterResult() = default;
    ScatterResult(Ray ray, m3d::vec3 color, bool scattered) : ray(ray), color(color), scattered(scattered) {}
};

struct Material {
    virtual ScatterResult scatter(const Ray& ray, const Hitpoint hp) const = 0;
};

struct Diffuse : public Material {
    m3d::vec3 color;

    Diffuse(m3d::vec3 color) : color(color) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint hp) const;
};

struct Shiny : public Material {
    m3d::vec3 color;
    float32 fuzz;

    Shiny(m3d::vec3 color, float32 fuzz) : color(color), fuzz(fuzz) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint hp) const;
};

struct Dielectric : public Material {
    m3d::vec3 color;
    float32 refIdx;

    Dielectric(m3d::vec3 color, float32 refIdx) : color(color), refIdx(refIdx) {}

    ScatterResult scatter(const Ray& ray, const Hitpoint hp) const;
};

#endif // MATERIALS_HPP
