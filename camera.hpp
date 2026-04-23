#ifndef CAMERA_HPP
#define CAMERA_HPP

// Std includes

// Local includes
#include "types.h"
#include "math.hpp"

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
    Camera(Vec3 pos, Vec3 lookat, Viewport viewport);

    Vec3 getPixelDelta() const;
    Vec3 getPixelDeltaX() const;
    Vec3 getPixelDeltaY() const;
    Vec3 getPixelOrigin() const;
    Vec3 getPixel(int32 x, int32 y) const;
    Vec3 getPos() const;
    Vec3 getDir() const;

private:
    Viewport viewport;
    Vec3 pos, dir, up, right;
    Vec3 pixelDelta, pixelOrigin;
};

#endif // CAMERA_HPP
