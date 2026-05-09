#include <math/util.hpp>

// Std inludes
#include <cmath>
#include <random>

using namespace m3d;

namespace math {

// Utility

float32 gammaCorrect(float32 val) {
    if (val <= 0.0f) {
        return 0.0f;
    }
    if (val <= 0.0031308f) {
        return 12.92f * val;
    }
    return 1.055f * std::pow(val, 1.0f / 2.4f) - 0.055f;
}

vec3 gammaCorrect(const vec3& color) {
    return vec3(gammaCorrect(color.x), gammaCorrect(color.y), gammaCorrect(color.z));
}

int32 clamp(int32 val, int32 min, int32 max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

float32 clamp(float32 val, float32 min, float32 max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

vec3 clamp(const vec3& vec, float32 min, float32 max) {
    return vec3(clamp(vec.x, min, max), clamp(vec.y, min, max), clamp(vec.z, min, max));
}

// Random utility

static thread_local std::mt19937 rng(std::random_device{}());
static thread_local std::uniform_real_distribution<float32> dist(0.0f, 1.0f);

float32 randomUnit() {
    return dist(rng);
}

vec3 randomUV() {
    float32 u = randomUnit();
    float32 v = randomUnit();

    float32 theta = 2.0f * PI * u;
    float32 phi = std::acos(1.0f - 2.0f * v);

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
    vec3 v = normalize(normal + randomUV());
    if (v.lenSq() == 0.0f) {
        return normal;
    }
    return v;
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
    float32 sin = std::sqrt(std::max(0.0f, 1.0f - cos * cos));
    float32 idx = n1 / n2;
    if (sin * idx > 1.0f || reflectance(cos, n1, n2) > randomUnit()) {
        return dir + 2.0f * cos * normal;
    }
    vec3 perp = idx * (dir + cos * normal);
    vec3 para = -std::sqrt(std::fabs(1.0f - lenSq(perp))) * normal;
    return perp + para;
}

float32 reflectance(float32 cos, float32 n1, float32 n2) {
    float32 r0 = (n1 - n2) / (n1 + n2);
    r0 *= r0;
    return r0 + (1.0f - r0) * std::pow((1.0f - cos), 5);
}

} // namespace math
