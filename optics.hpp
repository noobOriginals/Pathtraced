#ifndef OPTICS_HPP
#define OPTICS_HPP

// Std includes
#include <cmath>

// Local includes
#include "m3d.hpp"

m3d::vec3 reflect(const m3d::vec3& v, const m3d::vec3& normal) {
    return v - 2.0f * m3d::dot(v, normal) * normal;
}

m3d::vec3 refract(const m3d::vec3& dir, const m3d::vec3& normal, m3d::float32 insideRefIdx, m3d::float32 outsideRefIdx) {
    m3d::vec3 n = normal;
    m3d::float32 refIdx = outsideRefIdx / insideRefIdx;
    if (m3d::dot(dir, n) > 0) {
        n = -n;
        refIdx = insideRefIdx / outsideRefIdx;
    }
    m3d::vec3 perp = refIdx * (dir + m3d::dot(-dir, n) * n);
    m3d::vec3 para = -std::sqrt(std::fabs(1.0f - m3d::lenSq(perp))) * n;
    return perp + para;
}

m3d::vec3 refract(const m3d::vec3& vDir, const m3d::vec3& normal, m3d::float32 refIdx) {
    return refract(vDir, normal, refIdx, 1.0);
}

#endif // OPTICS_HPP