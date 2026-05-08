#include <material/material.hpp>

// Local includes
#include <util.hpp>

using namespace m3d;

namespace mat {

// Material

Material::Material(MaterialType type, const vec3& color, float32 param) : type(type), color(color), param(param) {}

ScatterResult Material::scatter(const Ray& ray, const Hitpoint& hp) const {
    switch (type) {
    case DIFFUSE: {
        return ScatterResult(Ray(
            hp.p,
            diffuse(hp.normal)
        ), color, true);
    }

    case METAL: {
        return ScatterResult(Ray(
            hp.p,
            reflect(ray.dir, hp.normal) + randomUV() * param
        ), color, true);
    }

    case DIELECTRIC: {
        return ScatterResult(Ray(
            hp.p,
            refract(ray.dir, hp.normal, (hp.exit) ? param : UTIL_AIR_REF_IDX, (hp.exit) ? UTIL_AIR_REF_IDX : param)
        ), color, true);
    }
    }
}

} // namespace mat