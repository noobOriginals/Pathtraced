#include "materials.hpp"

using namespace m3d;

ScatterResult scatterLambertian(const Ray& ray, const Hitpoint& hp, const vec3& color) {
    return ScatterResult(Ray(hp.p, diffuse(hp.normal)), color, true);
}

ScatterResult scatterMetal(const Ray& ray, const Hitpoint& hp, const vec3& color, float32 fuzz) {
    return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal) + randomUV() * fuzz), color, true);
}

ScatterResult scatterDielectric(const Ray& ray, const Hitpoint& hp, const vec3& color, float32 n1, float32 n2) {
    vec3 n = hp.normal;
    if (dot(ray.dir, n) > 0) {
        n = -n;
        float32 tmp = n1;
        n1 = n2;
        n2 = tmp;
    }

    float32 cos = dot(-ray.dir, n);
    float32 sin = std::sqrt(1.0f - cos * cos);
    if (sin * n1 / n2 > 1.0f || reflectance(cos, n1, n2) > randomUnit()) {
        return ScatterResult(Ray(hp.p, reflect(ray.dir, hp.normal)), color, true);
    }

    return ScatterResult(Ray(hp.p, refract(ray.dir, n, n1, n2)), color, true);
}

// Material

Material::Material(int32 type, vec3 color, float32 param) {
    this->type = type;
    this->color = color;
    if (type == METAL) {
        fuzz = param;
    } else if (type == DIELECTRIC) {
        refIdx = param;
    }
}

ScatterResult Material::scatter(const Ray& ray, const Hitpoint& hp) const {
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
