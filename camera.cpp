#include "camera.hpp"

// Std includes
#include <cmath>

// Local includes
#include "util.hpp"

// Camera

Camera::Camera(Vec3 pos, Vec3 lookat, float32 aspectRatio, float32 hfov, int32 pixelsX) {
    int32 pixelsY = pixelsX / aspectRatio;
    float32 viewportWidth = 2.0 * std::tan(degToRad(hfov) / 2.0);
}
