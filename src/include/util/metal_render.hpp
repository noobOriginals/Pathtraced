#ifndef UTIL_METAL_RENDER_HPP
#define UTIL_METAL_RENDER_HPP

#ifdef __APPLE__

#include <memory>
#include <string>

#include <scene/scene.hpp>
#include <util/render.hpp>

namespace util {

class MetalRenderer {
public:
    MetalRenderer(const scene::Scene& scn, const RenderParameters& params);
    ~MetalRenderer();

    void render();
    void save(std::string filepath) const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
    int width, height;
};

} // namespace util

#endif // __APPLE__
#endif // UTIL_METAL_RENDER_HPP
