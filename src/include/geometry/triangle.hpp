#ifndef GEO_TRIANGLE_HPP
#define GEO_TRIANGLE_HPP

// Std includes
#include <string>


// Local includes
#include <geometry/hittable.hpp>

namespace geo {

class Triangle : public Hittable {
public:
    Triangle() = default;
    Triangle(const m3d::vec3& a, const m3d::vec3& b, const m3d::vec3& c);
    Hittable* clone() const override;

    bool hit(const math::Ray& ray, math::Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const override;
    std::string toString() const override;
    int getType() const override;
    m3d::vec3 getA() const;
    m3d::vec3 getB() const;
    m3d::vec3 getC() const;

private:
    m3d::vec3 a, b, c, ab, ac, normal;
};

} // namespace geo

#endif // GEO_TRIANGLE_HPP