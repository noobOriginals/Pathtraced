#ifndef UTIL_HPP
#define UTIL_HPP

// Std includes

// Local includes
#include "m3d.hpp"

m3d::float32 clamp(m3d::float32 val, m3d::float32 min, m3d::float32 max);
m3d::vec3 clamp(m3d::vec3 vec, m3d::float32 min, m3d::float32 max);

class Interval {
public:

private:
    m3d::float32 min, max;
};

#endif // UTIL_HPP
