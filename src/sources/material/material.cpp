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

    default: {
        return ScatterResult();
    }
    }
}

std::string Material::toString() const {
    std::string str, ending;
    switch (type) {
    case DIFFUSE: {
        str = "Diffuse ";
        ending = "";
        break;
    }

    case METAL: {
        str = "Metal ";
        ending = std::to_string(param);
        break;
    }

    case DIELECTRIC: {
        str = "Dielectric ";
        ending = std::to_string(param);
        break;
    }

    default: {
        str = " ";
        ending = "";
    }
    }
    str += std::to_string(color.x) + " ";
    str += std::to_string(color.y) + " ";
    str += std::to_string(color.z) + " ";
    str += ending;
    return str;
}

} // namespace mat