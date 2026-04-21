#ifndef CAMERA_HPP
#define CAMERA_HPP

// Std includes


// Local includes
#include "types.h"
#include "math.hpp"

class Camera {
public:
    Camera(Vec3 pos, Vec3 lookat, float32 aspectRatio, float32 hfov, int32 pixelsX);

private:

};

#endif // CAMERA_HPP
