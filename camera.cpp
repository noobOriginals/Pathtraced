#include "camera.hpp"

// Std includes
#include <cmath>

// Local includes

using namespace m3d;

// Viewport

Viewport::Viewport(int32 screenWidth, int32 screenHeight, float32 vfov) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->vfov = vfov;
    aspectRatio = (float32)screenWidth / screenHeight;
    height = std::tan(vfov / 2.0);
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

Camera::Camera(vec3 pos, vec3 lookat, Viewport viewport) {
    setPosition(pos);
    setLookat(lookat);
    setViewport(viewport);
    computeValues();
}

void Camera::setPosition(vec3 pos) {
    this->pos = pos;
}

void Camera::setLookat(vec3 lookat) {
    this->lookat = lookat;
}

void Camera::setViewport(Viewport viewport) {
    this->viewport = viewport;
}

void Camera::computeValues() {
    vec3 worldUp = vec3(0.0, 1.0, 0.0);

    dir = normalize(lookat - pos);
    right = normalize(cross(dir, worldUp));
    up = normalize(cross(right, dir));

    pixelDeltaX = right * (viewport.getViewportWidth() / viewport.getScreenWidth());
    pixelDeltaY = up * (viewport.getViewportHeight() / viewport.getScreenHeight());
    pixelOrigin = pos + dir * 0.5 - right * (viewport.getViewportWidth() * 0.5) - up * (viewport.getViewportHeight() * 0.5) + pixelDeltaX * 0.5 + pixelDeltaY * 0.5;
}

vec3 Camera::getPixelDeltaX() const {
    return pixelDeltaX;
}
vec3 Camera::getPixelDeltaY() const {
    return pixelDeltaY;
}

vec3 Camera::getPixelOrigin() const {
    return pixelOrigin;
}

vec3 Camera::getPixel(int32 x, int32 y) const {
    return pixelOrigin + pixelDeltaX * x + pixelDeltaY * y;
}

vec3 Camera::getPos() const {
    return pos;
}

vec3 Camera::getDir() const {
    return dir;
}
