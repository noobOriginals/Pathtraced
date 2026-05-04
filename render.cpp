#include "render.hpp"

// Std includes
#include <cmath>

#ifndef NO_MULTITHREAD
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#endif

// Local includes
#include "util.hpp"

using namespace m3d;

float32 gammaCorrect(float32 f) {
    if (f > 0) {
        return std::sqrt(f);
    }
    return 0;
}

// Render

Render::Render(int32 width, int32 height, float32 verticalFOV) {
    viewport = Viewport(width, height, degToRad(verticalFOV));
    camera = Camera(vec3(), vec3(), viewport);
    image = Image(width, height);
}

Pixel Render::renderPixel(int32 x, int32 y) const {
    vec3 color = vec3(0.0);
    if (supersampling) {
        vec3 supersampleOrigin = camera.getPixel(x, y) - camera.getPixelDeltaX() * 0.5 + supersampleDeltaX - camera.getPixelDeltaY() * 0.5 + supersampleDeltaY;
        for (int32 sy = 0; sy < supersamplesY; sy++) {
            for (int32 sx = 0; sx < supersamplesX; sx++) {
                vec3 pixel = supersampleOrigin + supersampleDeltaX * sx + supersampleDeltaY * sy;
                Ray ray = Ray(camera.getPos(), normalize(pixel - camera.getPos()));
                color += raytrace(ray, maxDepth);
            }
        }
        color /= supersamplesX * supersamplesY;
    } else {
        color = raytrace(Ray(camera.getPos(), normalize(camera.getPixel(x, y) - camera.getPos())), maxDepth);
    }
    if (gammaCorrected) {
        color.x = gammaCorrect(color.x);
        color.y = gammaCorrect(color.y);
        color.z = gammaCorrect(color.z);
    }
    color = clamp(color, 0.0f, 1.0f);
    return Pixel(color);
}

#ifndef NO_MULTITHREAD
void Render::renderTile(int32 x0, int32 y0, int32 x1, int32 y1) const {
    int32 width = viewport.getScreenWidth();
    Pixel* pixels = image.getPixels(nullptr);
    for (int32 y = y0; y < y1; y++) {
        for (int32 x = x0; x < x1; x++) {
            pixels[y * width + x] = renderPixel(x, y);
        }
    }
}
#endif

void Render::render() {
    supersampleDeltaX = camera.getPixelDeltaX() / (supersamplesX + 1);
    supersampleDeltaY = camera.getPixelDeltaY() / (supersamplesY + 1);
    int32 width = viewport.getScreenWidth();
    int32 height = viewport.getScreenHeight();

#ifndef NO_MULTITHREAD
    if (!multithread) {
#endif
        Pixel* pixels = image.getPixels(nullptr);
        for (int32 y = 0; y < height; y++) {
            for (int32 x = 0; x < width; x++) {
                pixels[y * width + x] = renderPixel(x, y);
            }
        }
        return;
#ifndef NO_MULTITHREAD
    }

    std::queue<Tile> workQueue;

    for (int32 y = 0; y < height; y += tileSize) {
        for (int32 x = 0; x < width; x += tileSize) {
            workQueue.push({x, y, clamp(x + tileSize, 0, width), clamp(y + tileSize, 0, height)});
        }
    }

    std::mutex queueMutex;

    auto worker = [&]() {
        while (true) {
            Tile tile;
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                if (workQueue.empty()) {
                    return;
                }
                tile = workQueue.front();
                workQueue.pop();
            }
            renderTile(tile.x0, tile.y0, tile.x1, tile.y1);
        }
    };

    int32 nThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    for (int32 i = 0; i < nThreads; i++) {
        threads.emplace_back(worker);
    }
    for (auto& t : threads) {
        t.join();
    }
#endif
}

void Render::setCameraPos(vec3 pos) {
    camera.setPosition(pos);
    camera.computeValues();
}

void Render::setCameraLookat(vec3 lookat) {
    camera.setLookat(lookat);
    camera.computeValues();
}

void Render::setCameraPosAndLookat(vec3 pos, vec3 lookat) {
    camera.setPosition(pos);
    camera.setLookat(lookat);
    camera.computeValues();
}

void Render::setMaxDepth(int32 maxDepth) {
    this->maxDepth = maxDepth;
}

#ifndef NO_MULTITHREAD
void Render::setTileSize(int32 tileSize) {
    this->tileSize = tileSize;
}
#endif

void Render::setSupersamples(int32 samplesX, int32 samplesY) {
    supersamplesX = samplesX;
    supersamplesY = samplesY;
}

void Render::enableSupersamling() {
    supersampling = true;
}

void Render::disableSupersampling() {
    supersampling = false;
}

void Render::enableGammaCorrection() {
    gammaCorrected = true;
}

void Render::disableGammaCorrection() {
    gammaCorrected = false;
}

#ifndef NO_MULTITHREAD
void Render::enableMultithreading() {
    multithread = true;
}

void Render::disableMultithreading() {
    multithread = false;
}
#endif

void Render::save(std::string filename) const {
    image.save(filename);
}

const Image& Render::getImage() const {
    return image;
}

void Render::setRaytraceCallback(RaytraceCallback rt) {
    raytrace = rt;
}
