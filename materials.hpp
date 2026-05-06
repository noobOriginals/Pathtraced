#ifndef MATERIALS_HPP
#define MATERIALS_HPP

// Local includes
#include "m3d.hpp"
#include "geometry.hpp"
#include "optics.hpp"

#define LAMBERTIAN 0x10
#define METAL 0x11
#define DIELECTRIC 0x12
#define EMISSIVE 0x13 // To be added soon

struct ScatterResult {
    Ray ray;
    m3d::vec3 color;
    bool scattered;

    ScatterResult() = default;
    ScatterResult(Ray ray, m3d::vec3 color, bool scattered) : ray(ray), color(color), scattered(scattered) {}
};

ScatterResult scatterLambertian(const Ray& ray, const Hitpoint& hp, const m3d::vec3& color);
ScatterResult scatterMetal(const Ray& ray, const Hitpoint& hp, const m3d::vec3& color, m3d::float32 fuzz);
ScatterResult scatterDielectric(const Ray& ray, const Hitpoint& hp, const m3d::vec3& color, m3d::float32 n1, m3d::float32 n2);

struct Material {
    m3d::int32 type;
    m3d::vec3 color;
    m3d::float32 fuzz;
    m3d::float32 refIdx;

    Material(m3d::int32 type, m3d::vec3 color, m3d::float32 param = 0.0f);

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const;
};

#endif // MATERIALS_HPP
