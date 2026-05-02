#ifndef CAMERA_HPP
#define CAMERA_HPP

// Std includes
#include <vector>

// Local includes
#include "types.h"
#include "m3d.hpp"

class Viewport {
public:
    Viewport() = default;
    Viewport(int32 screenWidth, int32 screenHeight, float32 vfov);

    int32 getScreenWidth() const;
    int32 getScreenHeight() const;
    float32 getAspectRatio() const;
    float32 getVerticalFOV() const;
    float32 getViewportWidth() const;
    float32 getViewportHeight() const;

private:
    int32 screenWidth = 0, screenHeight = 0;
    float32 aspectRatio = 0.0, vfov = 0.0, width = 0.0, height = 0.0;
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
    m3d::vec3 getPixel(int32 x, int32 y) const;
    m3d::vec3 getPos() const;
    m3d::vec3 getDir() const;

private:
    Viewport viewport;
    m3d::vec3 pos, lookat, dir, up, right;
    m3d::vec3 pixelDeltaX, pixelDeltaY, pixelOrigin;
};

#endif // CAMERA_HPP
