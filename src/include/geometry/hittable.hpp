#ifndef GEO_HITTABLE_HPP
#define GEO_HITTABLE_HPP

// Std includes
#include <string>

// Local includes
#include <lib/m3d.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>

namespace geo {

class Hittable {
public:
    virtual ~Hittable() {}
    virtual bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const = 0;
    virtual std::string toString() const = 0;
};

} // namespace geo

#endif // GEO_HITTABLE_HPP