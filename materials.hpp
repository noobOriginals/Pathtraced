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

ScatterResult scatterLambertian(const Ray& ray, const Hitpoint& hp, const m3d::vec3& color) {
    return ScatterResult(Ray(hp.p, diffuse(hp.normal)), color, true);
}

ScatterResult scatterMetal(const Ray& ray, const Hitpoint& hp, const m3d::vec3& color, m3d::float32 fuzz) {
    return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal) + randomUV() * fuzz), color, true);
}

ScatterResult scatterDielectric(const Ray& ray, const Hitpoint& hp, const m3d::vec3& color, m3d::float32 n1, m3d::float32 n2) {
    m3d::vec3 n = hp.normal;
    if (m3d::dot(ray.dir, n) > 0) {
        n = -n;
        m3d::float32 tmp = n1;
        n1 = n2;
        n2 = tmp;
    }

    m3d::float32 cos = dot(-ray.dir, n);
    m3d::float32 sin = std::sqrt(1.0f - cos * cos);
    if (sin * n1 / n2 > 1.0f || reflectance(cos, n1, n2) > randomUnit()) {
        return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal)), color, true);
    }

    return ScatterResult(Ray(hp.p, refract(ray.dir, n, n1, n2)), color, true);
}

struct Material {
    m3d::int32 type;
    m3d::vec3 color;
    m3d::float32 fuzz;
    m3d::float32 refIdx;

    Material(m3d::int32 type, m3d::vec3 color, m3d::float32 param = 0.0f) {
        this->type = type;
        this->color = color;
        if (type == METAL) {
            fuzz = param;
        } else if (type == DIELECTRIC) {
            refIdx = param;
        }
    }

    ScatterResult scatter(const Ray& ray, const Hitpoint& hp) const {
        switch (type) {
        case LAMBERTIAN: {
            return scatterLambertian(ray, hp, color);
            break;
        }

        case METAL: {
            return scatterMetal(ray, hp, color, fuzz);
            break;
        }

        case DIELECTRIC: {
            return scatterDielectric(ray, hp, color, OPTICS_AIR_REF_IDX, refIdx);
            break;
        }

        default: {
            return ScatterResult();
        }
        }
    }
};

#endif // MATERIALS_HPP
