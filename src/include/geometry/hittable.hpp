#ifndef GEO_HITTABLE_HPP
#define GEO_HITTABLE_HPP

// Std includes
#include <string>

// Local includes
#include <lib/m3d.hpp>
#include <math/ray.hpp>
#include <math/hitpoint.hpp>

namespace geo {

class Hittable {
public:
    virtual ~Hittable() {}
    virtual Hittable* clone() const = 0;
    virtual bool hit(const math::Ray& ray, math::Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const = 0;
    virtual std::string toString() const = 0;
    virtual int getType() const = 0;
};

} // namespace geo

#endif // GEO_HITTABLE_HPP