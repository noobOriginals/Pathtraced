#ifndef GEO_SPHERE_HPP
#define GEO_SPHERE_HPP

// Std includes
#include <string>


// Local includes
#include <geometry/hittable.hpp>

namespace geo {

class Sphere : public Hittable {
public:
    Sphere() = default;
    Sphere(const m3d::vec3& center, m3d::float32 radius);
    Hittable* clone() const override;

    bool hit(const math::Ray& ray, math::Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const override;
    std::string toString() const override;

private:
    m3d::vec3 center;
    m3d::float32 radius;
};

} // namespace geo

#endif // GEO_SPHERE_HPP