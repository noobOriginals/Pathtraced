#ifndef UTIL_HPP
#define UTIL_HPP

// Std includes

// Local includes
#include "types.h"
#include "m3d.hpp"

float32 clamp(float32 val, float32 min, float32 max);
m3d::vec3 clamp(m3d::vec3 vec, float32 min, float32 max);

class Interval {
public:

private:
    float32 min, max;
};

#endif // UTIL_HPP
