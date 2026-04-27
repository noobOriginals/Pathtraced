#ifndef RENDER_HPP
#define RENDER_HPP

// Std includes
#include <string>

// Local includes
#include "types.h"
#include "util.hpp"
#include "math.hpp"
#include "geometry.hpp"
#include "camera.hpp"
#include "image.hpp"

typedef Vec3 (*RaytraceCallback)(const Ray& ray);

class Render {
public:
    Render() = default;
    Render(int32 width, int32 height, float32 verticalFOV);

    void begin() const;
    const bool& isDone() const;

    void setCameraPos(Vec3 pos);
    void setCameraLookat(Vec3 lookat);
    void setCameraPosAndLookat(Vec3 pos, Vec3 lookat);

    void setSupersamples(int32 samplesX, int32 samplesY);
    void enableSupersamling();
    void disableSupersampling();

    void save(std::string filename) const;
    const Image& getImage() const;

    void setRaytraceCallback(RaytraceCallback rt);

private:
    RaytraceCallback raytrace = nullptr;

    Viewport viewport;
    Camera camera;
    mutable Image image;
    int32 supersamplesX = 0, supersamplesY = 0;
    bool supersampling = false;
    mutable bool done = true;
};

#endif // RENDER_HPP