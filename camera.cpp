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
    float32 focal2 = 0.8;
    height = focal2 * std::tan(vfov / 2.0);
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
    right = cross(dir, worldUp);
    up = cross(right, dir);

    pixelDelta = vec3(viewport.getViewportWidth() / viewport.getScreenWidth(), viewport.getViewportHeight() / viewport.getScreenHeight(), 0.0);
    pixelOrigin = pos + dir - right * (viewport.getViewportWidth() / 2.0) - up * (viewport.getViewportHeight() / 2.0) + pixelDelta / 2.0;
}

vec3 Camera::getPixelDelta() const {
    return pixelDelta;
}

vec3 Camera::getPixelDeltaX() const {
    return vec3(pixelDelta.x, 0.0, 0.0);
}

vec3 Camera::getPixelDeltaY() const {
    return vec3(pixelDelta.y, 0.0, 0.0);
}

vec3 Camera::getPixelOrigin() const {
    return pixelOrigin;
}

vec3 Camera::getPixel(int32 x, int32 y) const {
    return pixelOrigin + pixelDelta * vec3(x, y, 0.0);
}

vec3 Camera::getPos() const {
    return pos;
}

vec3 Camera::getDir() const {
    return dir;
}
