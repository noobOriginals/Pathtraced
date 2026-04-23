#ifndef UTIL_HPP
#define UTIL_HPP

// Std includes

// Local includes
#include "types.h"
#include "math.hpp"

#define UTIL_PI 3.14159265358979323846
#define UTIL_EPSILON 1e-6

float32 degToRad(float32 deg);
float32 radToDeg(float32 rad);
float32 clamp(float32 val, float32 min, float32 max);
Vec3 clamp(Vec3 vec, float32 min, float32 max);

class Interval {
public:

private:
    float32 min, max;
};

#endif // UTIL_HPP
