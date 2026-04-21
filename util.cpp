#include "util.hpp"

float32 degToRad(float32 deg) {
    return deg * UTIL_PI / 180.0f;
}

float32 radToDeg(float32 rad) {
    return rad * 180.0f / UTIL_PI;
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

Vec3 clamp(Vec3 vec, float32 min, float32 max) {
    if (vec.x < min) {
        vec.x = min;
    }
    if (vec.x > max) {
        vec.x = max;
    }
    if (vec.y < min) {
        vec.y = min;
    }
    if (vec.y > max) {
        vec.y = max;
    }
    if (vec.z < min) {
        vec.z = min;
    }
    if (vec.z > max) {
        vec.z = max;
    }
    return vec;
}
