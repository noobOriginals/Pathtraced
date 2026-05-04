#ifndef RENDER_HPP
#define RENDER_HPP

// #define NO_MULTITHREAD // If your compiler does not support the multithreading features used

// Std includes
#include <string>

// Local includes
#include "types.h"
#include "util.hpp"
#include "m3d.hpp"
#include "geometry.hpp"
#include "camera.hpp"
#include "image.hpp"

typedef m3d::vec3 (*RaytraceCallback)(const Ray& ray, int32 depth);

class Render {
public:
    Render() = default;
    Render(int32 width, int32 height, float32 verticalFOV);

    void render();

    void setCameraPos(m3d::vec3 pos);
    void setCameraLookat(m3d::vec3 lookat);
    void setCameraPosAndLookat(m3d::vec3 pos, m3d::vec3 lookat);

    void setMaxDepth(int32 maxDepth);

#ifndef NO_MULTITHREAD
    void setTileSize(int32 tileSize);
#endif

    void setSupersamples(int32 samplesX, int32 samplesY);
    void enableSupersamling();
    void disableSupersampling();
    void enableGammaCorrection();
    void disableGammaCorrection();

#ifndef NO_MULTITHREAD
    void enableMultithreading();
    void disableMultithreading();
#endif

    void save(std::string filename) const;
    const Image& getImage() const;

    void setRaytraceCallback(RaytraceCallback rt);

private:
    struct Tile {
        int32 x0, y0, x1, y1;
    };

    Pixel renderPixel(int32 x, int32 y) const;
    void renderTile(int32 x0, int32 y0, int32 x1, int32 y1) const;

    RaytraceCallback raytrace = nullptr;

    Viewport viewport;
    Camera camera;
    Image image;

    int32 supersamplesX = 0, supersamplesY = 0;
    m3d::vec3 supersampleDeltaX, supersampleDeltaY;

    bool supersampling = false;
    bool gammaCorrected = false;
    int32 maxDepth = 1;

#ifndef NO_MULTITHREAD
    bool multithread = false;
    int32 tileSize = 100;
#endif
};

#endif // RENDER_HPP