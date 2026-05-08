#include "optics.hpp"

// Std inludes
#include <cmath>
#include <random>

using namespace m3d;

// Random utility

static thread_local std::mt19937 rng(std::random_device{}());
static thread_local std::uniform_real_distribution<float32> dist(0.0f, 1.0f);

float32 randomUnit() {
    return dist(rng);
}

vec3 randomUV() {
    float32 u = randomUnit();
    float32 v = randomUnit();

    float32 theta = 2.0f * m3d::PI * u;
    float32 phi   = std::acos(1.0f - 2.0f * v);

    return vec3(
        std::sin(phi) * std::cos(theta),
        std::sin(phi) * std::sin(theta),
        std::cos(phi)
    );
}

vec3 randomOnHemisphere(const vec3& normal) {
    vec3 v = randomUV();
    return dot(v, normal) > 0.0f ? v : -v;
}

vec3 randomCosineHemisphere(const vec3& normal) {
    float32 u = randomUnit(), v = randomUnit();
    float32 r = std::sqrt(u);
    float32 theta = 2.0f * m3d::PI * v;

    vec3 up = std::abs(normal.x) > 0.9f ? vec3(0.0f, 1.0f, 0.0f) : vec3(1.0f, 0.0f, 0.0f);
    vec3 tangent =  cross(up, normal);
    vec3 bitangent = cross(normal, tangent);

    return tangent * (r * std::cos(theta)) + bitangent * (r * std::sin(theta)) + normal * std::sqrt(1.0f - u);
}

// Optics

vec3 diffuse(const vec3& normal) {
    return randomCosineHemisphere(normal);
}

vec3 reflect(const vec3& v, const vec3& normal) {
    return v - 2.0f * dot(v, normal) * normal;
}

vec3 refract(const vec3& dir, const vec3& normal, float32 n1, float32 n2) {
    float32 cos = dot(-dir, normal);
    float32 sin = std::sqrt(1.0f - cos * cos);
    if (sin * n1 / n2 > 1.0f || reflectance(cos, n1, n2) > randomUnit()) {
        return dir + 2.0f * cos * normal;
    }
    vec3 perp = (n1 / n2) * (dir + cos * normal);
    vec3 para = -std::sqrt(std::fabs(1.0f - lenSq(perp))) * normal;
    return perp + para;
}

float32 reflectance(float32 cos, float32 n1, float32 n2) {
    float32 r0 = (n1 - n2) / (n1 + n2);
    r0 *= r0;
    return r0 + (1.0f - r0) * std::pow((1.0f - cos), 5);
}
