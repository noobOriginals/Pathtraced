#include <geometry/sphere.hpp>

// Std includes
#include <cmath>

using namespace m3d;

namespace geo {

// Sphere

Sphere::Sphere(const vec3& center, float32 radius) : center(center), radius(radius) {}

bool Sphere::hit(const Ray& ray, Hitpoint& hp, float32 minT, float32 maxT) const {
    vec3 rayToSphere = center - ray.org;

    float32 a = lenSq(ray.dir);
    float32 h = dot(ray.dir, rayToSphere);
    float32 c = lenSq(rayToSphere) - radius * radius;
    float32 delta = h * h - a * c;

    if (delta < EPSILON) {
        return false;
    }

    float32 sqrtd = std::sqrt(delta);
    float32 invA = 1.0 / a;

    hp.t = (h - sqrtd) * invA;

    if (hp.t < minT) {
        hp.t = (h + sqrtd) * invA;
    }

    if (hp.t < minT || hp.t > maxT) {
        return false;
    }

    hp.p = ray.at(hp.t);
    hp.setNormal(ray.dir, (hp.p - center) / radius);

    return true;
}

} // namespace geo
