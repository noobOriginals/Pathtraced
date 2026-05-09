#ifndef GEO_QUAD_HPP
#define GEO_QUAD_HPP

// Std includes
#include <string>


// Local includes
#include <geometry/hittable.hpp>

namespace geo {

class Quad : public Hittable {
public:
    Quad() = default;
    Quad(const m3d::vec3& center, const m3d::vec3& u, const m3d::vec3& v);
    Hittable* clone() const override;

    bool hit(const Ray& ray, Hitpoint& hp, m3d::float32 minT, m3d::float32 maxT) const override;
    std::string toString() const override;

private:
    m3d::vec3 center, origin, u, v, normal;
    m3d::float32 uu, vv, uv, invProjectionDenom;
};

} // namespace geo

#endif // GEO_QUAD_HPP