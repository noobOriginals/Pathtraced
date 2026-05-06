#ifndef CAMERA_HPP
#define CAMERA_HPP

// Std includes
#include <vector>

// Local includes
#include "m3d.hpp"

class Viewport {
public:
    Viewport() = default;
    Viewport(m3d::int32 screenWidth, m3d::int32 screenHeight, m3d::float32 vfov);

    m3d::int32 getScreenWidth() const;
    m3d::int32 getScreenHeight() const;
    m3d::float32 getAspectRatio() const;
    m3d::float32 getVerticalFOV() const;
    m3d::float32 getViewportWidth() const;
    m3d::float32 getViewportHeight() const;

private:
    m3d::int32 screenWidth = 0, screenHeight = 0;
    m3d::float32 aspectRatio = 0.0, vfov = 0.0, width = 0.0, height = 0.0;
};

class Camera {
public:
    Camera() = default;
    Camera(m3d::vec3 pos, m3d::vec3 lookat, Viewport viewport);

    void setPosition(m3d::vec3 pos);
    void setLookat(m3d::vec3 lookat);
    void setViewport(Viewport viewport);

    void computeValues();

    m3d::vec3 getPixelDeltaX() const;
    m3d::vec3 getPixelDeltaY() const;
    m3d::vec3 getPixelOrigin() const;
    m3d::vec3 getPixel(m3d::int32 x, m3d::int32 y) const;
    m3d::vec3 getPos() const;
    m3d::vec3 getDir() const;
    m3d::vec3 getLookat() const;

private:
    Viewport viewport;
    m3d::vec3 pos, lookat, dir, up, right;
    m3d::vec3 pixelDeltaX, pixelDeltaY, pixelOrigin;
};

#endif // CAMERA_HPP
