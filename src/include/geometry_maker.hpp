#ifndef GEOMETRY_MAKER_HPP
#define GEOMETRY_MAKER_HPP

// Local includes
#include <lib/m3d.hpp>
#include <geometry/sphere.hpp>
#include <geometry/quad.hpp>
#include <geometry/triangle.hpp>

geo::Sphere makeSphere(const m3d::vec3& center, m3d::float32 radius, const m3d::vec3& translation = m3d::vec3()) {
    return geo::Sphere(center + translation, radius);
}

geo::Triangle makeTriangle(const m3d::vec3& a, const m3d::vec3& b, const m3d::vec3& c, const m3d::vec3& trnaslation = m3d::vec3(), m3d::float32 angleDeg = 0.0, const m3d::vec3& axis = m3d::vec3(0, 1, 0)) {
    m3d::mat4 transform = rotate(translate(trnaslation), m3d::degToRad(angleDeg), axis);
    return geo::Triangle(
        m3d::vec3(transform * m3d::vec4(a, 1.0)),
        m3d::vec3(transform * m3d::vec4(b, 1.0)),
        m3d::vec3(transform * m3d::vec4(c, 1.0))
    );
}

geo::Quad makeQuad(const m3d::vec3& center, const m3d::vec3& u, const m3d::vec3& v, const m3d::vec3& trnaslation = m3d::vec3(), m3d::float32 angleDeg = 0.0, const m3d::vec3& axis = m3d::vec3(0, 1, 0)) {
    m3d::mat4 transform = rotate(m3d::degToRad(angleDeg), axis);
    return geo::Quad(
        center + trnaslation,
        m3d::vec3(transform * m3d::vec4(u, 1.0)),
        m3d::vec3(transform * m3d::vec4(v, 1.0))
    );
}

#endif // GEOMETRY_MAKER_HPP