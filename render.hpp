#ifndef RENDER_HPP
#define RENDER_HPP

// #define NO_MULTITHREAD // If your compiler does not support the multithreading features used

// Std includes
#include <string>

// Local includes
#include "util.hpp"
#include "m3d.hpp"
#include "geometry.hpp"
#include "camera.hpp"
#include "image.hpp"

class Render;
typedef m3d::vec3 (*RenderRaytraceCallback)(const Render* render, const Ray& ray, m3d::int32 depth);

m3d::float32 gammaCorrect(m3d::float32 f);

class Render {
public:
    Render() = default;
    Render(m3d::int32 width,  m3d::int32 height,  m3d::float32 verticalFOV);

    void render();

    void setCameraPos(m3d::vec3 pos);
    void setCameraLookat(m3d::vec3 lookat);
    void setCameraPosAndLookat(m3d::vec3 pos, m3d::vec3 lookat);

    void setMaxDepth(m3d::int32 maxDepth);

#ifndef NO_MULTITHREAD
    void setTileSize(m3d::int32 tileSize);
#endif

    void setSupersamples(m3d::int32 samplesX, m3d::int32 samplesY);
    void enableSupersamling();
    void disableSupersampling();
    void enableGammaCorrection();
    void disableGammaCorrection();

#ifndef NO_MULTITHREAD
    void enableMultithreading();
    void disableMultithreading();
#endif

    void save(std::string filename) const;

    const Viewport& getViewport() const;
    const Camera& getCamera() const;
    const Image& getImage() const;
    m3d::int32 getSupersamplesX() const;
    m3d::int32 getSupersamplesY() const;
    bool isSupersampling() const;
    bool isGammaCorrected() const;
    m3d::int32 getMaxDepth() const;

#ifndef NO_MULTITHREAD
    bool isMultithread() const;
    m3d::int32 getTileSize() const;
#endif

    void setRaytraceCallback(RenderRaytraceCallback rt);

    void setUserPtr(void* userPtr);
    void* getUserPtr() const;

private:
    struct Tile {
        m3d::int32 x0, y0, x1, y1;
    };

    Pixel renderPixel(m3d::int32 x, m3d::int32 y) const;
    void renderTile(m3d::int32 x0, m3d::int32 y0, m3d::int32 x1, m3d::int32 y1) const;

    RenderRaytraceCallback raytrace = nullptr;

    Viewport viewport;
    Camera camera;
    Image image;

    m3d::int32 supersamplesX = 0, supersamplesY = 0;
    m3d::vec3 supersampleDeltaX, supersampleDeltaY;

    bool supersampling = false;
    bool gammaCorrected = false;
    m3d::int32 maxDepth = 1;

#ifndef NO_MULTITHREAD
    bool multithread = false;
    m3d::int32 tileSize = 100;
#endif

    void* userPtr = nullptr;
};

#endif // RENDER_HPP