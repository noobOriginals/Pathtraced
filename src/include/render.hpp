#ifndef RENDER_HPP
#define RENDER_HPP

// Std includes
#include <string>

// Local includes
#include <lib/image.hpp>
#include <lib/m3d.hpp>
#include <ray.hpp>

typedef m3d::vec3 (*RenderRaytraceCallback)(const Ray& ray, m3d::int32 maxBounces);

struct RenderParameters {
    m3d::int32 screenWidth = 800;
    m3d::int32 screenHeight = 600;
    m3d::float32 vfov = 25.0f;
    m3d::float32 focalLength = 0.5f;

    m3d::vec3 cameraPos;
    m3d::vec3 cameraLookAt;
    m3d::vec3 worldUp;

    m3d::int32 maxBounces = 10;
    m3d::int32 samplesPerPixel = 0;
    m3d::int32 threadTileSize = 100;
    bool enableSupersampling = false;
    bool enableGammaCorrection = false;
    bool enableMultiThreading = true;

    // Leave at 0 for default which is the number of CPU cores available on the computer
    m3d::int32 threadCount = 0;

    RenderRaytraceCallback raytraceCallback = nullptr;
};

class Render {
public:
    Render() = default;
    Render(RenderParameters params);

    void render() const;
    void save(std::string filepath) const;

private:
    struct Tile {
        m3d::int32 x0, y0, x1, y1;
    };

    Pixel renderPixel(m3d::int32 x, m3d::int32 y) const;
    void renderTile(Tile t) const;

    m3d::int32 screenW, screenH;
    m3d::vec3 camPos, pixelDeltaW, pixelDeltaH, pixelOrigin;
    m3d::int32 maxBounces, samplesPerPixel, tileSize;
    bool supersampling, gammaCorrection, multiThreading;
    m3d::int32 threadCount;

    RenderRaytraceCallback raytraceCallback = nullptr;

    Image image;
};

#endif // RENDER_HPP