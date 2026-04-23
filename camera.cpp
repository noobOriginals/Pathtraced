#include "camera.hpp"

// Std includes
#include <cmath>

// Local includes

// Viewport

Viewport::Viewport(int32 screenWidth, int32 screenHeight, float32 vfov) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->vfov = vfov;
    aspectRatio = (float32)screenWidth / screenHeight;
    height = 2.0 * std::tan(vfov / 2.0);
    width = height * aspectRatio;
}

int32 Viewport::getScreenWidth() const {
    return screenWidth;
}

int32 Viewport::getScreenHeight() const {
    return screenHeight;
}

float32 Viewport::getAspectRatio() const {
    return aspectRatio;
}

float32 Viewport::getVerticalFOV() const {
    return vfov;
}

float32 Viewport::getViewportWidth() const {
    return width;
}

float32 Viewport::getViewportHeight() const {
    return height;
}


// Camera

Camera::Camera(Vec3 pos, Vec3 lookat, Viewport viewport) {
    Vec3 worldUp = Vec3(0.0, 1.0, 0.0);

    this->pos = pos;

    dir = normalize(lookat - pos);
    right = cross(dir, worldUp);
    up = cross(right, dir);

    pixelDelta = Vec3(viewport.getViewportWidth() / viewport.getScreenWidth(), viewport.getViewportHeight() / viewport.getScreenHeight(), 0.0);
    pixelOrigin = pos + dir - right * (viewport.getViewportWidth() / 2.0) - up * (viewport.getViewportHeight() / 2.0) + pixelDelta / 2.0;
}

Vec3 Camera::getPixelDelta() const {
    return pixelDelta;
}

Vec3 Camera::getPixelDeltaX() const {
    return Vec3(pixelDelta.x, 0.0, 0.0);
}

Vec3 Camera::getPixelDeltaY() const {
    return Vec3(pixelDelta.y, 0.0, 0.0);
}

Vec3 Camera::getPixelOrigin() const {
    return pixelOrigin;
}

Vec3 Camera::getPixel(int32 x, int32 y) const {
    return pixelOrigin + pixelDelta * Vec3(x, y, 0.0);
}

Vec3 Camera::getPos() const {
    return pos;
}

Vec3 Camera::getDir() const {
    return dir;
}
