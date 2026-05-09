#ifdef __APPLE__

#include <util/metal_render.hpp>
#include <util/gpu_scene.hpp>

// Geometry headers for dynamic_cast-based type inspection
#include <geometry/sphere.hpp>
#include <geometry/triangle.hpp>
#include <geometry/quad.hpp>
#include <scene/object.hpp>
#include <lib/image.hpp>
#include <lib/m3d.hpp>
#include <math/util.hpp>

// System
#include <cmath>
#include <iostream>
#include <vector>
#include <mach-o/dyld.h>

// Metal
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

using namespace m3d;

// ---------------------------------------------------------------------------
// Pimpl
// ---------------------------------------------------------------------------

struct util::MetalRenderer::Impl {
    id<MTLDevice>                device;
    id<MTLCommandQueue>          queue;
    id<MTLComputePipelineState>  pipeline;
    id<MTLBuffer>                objectsBuf;
    id<MTLBuffer>                paramsBuf;
    id<MTLTexture>               outTexture;
    int                          width;
    int                          height;
};

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static NSString* execDir() {
    char buf[PATH_MAX];
    uint32_t size = sizeof(buf);
    _NSGetExecutablePath(buf, &size);
    NSString* execPath = [[NSString stringWithUTF8String:buf]
                           stringByResolvingSymlinksInPath];
    return [execPath stringByDeletingLastPathComponent];
}

static GPUObject toGPUObject(const scene::Object& obj) {
    GPUObject g = {};

    if (auto* s = dynamic_cast<geo::Sphere*>(obj.h)) {
        g.type = 0;
        vec3 c = s->getCenter();
        g.d[0] = c.x; g.d[1] = c.y; g.d[2] = c.z;
        g.d[3] = s->getRadius();
    } else if (auto* t = dynamic_cast<geo::Triangle*>(obj.h)) {
        g.type = 1;
        vec3 a = t->getA(), b = t->getB(), c = t->getC();
        g.d[0]=a.x; g.d[1]=a.y; g.d[2]=a.z;
        g.d[3]=b.x; g.d[4]=b.y; g.d[5]=b.z;
        g.d[6]=c.x; g.d[7]=c.y; g.d[8]=c.z;
    } else if (auto* q = dynamic_cast<geo::Quad*>(obj.h)) {
        g.type = 2;
        vec3 center = q->getCenter(), u = q->getU(), v = q->getV();
        g.d[0]=center.x; g.d[1]=center.y; g.d[2]=center.z;
        g.d[3]=u.x; g.d[4]=u.y; g.d[5]=u.z;
        g.d[6]=v.x; g.d[7]=v.y; g.d[8]=v.z;
    }

    g.matType = (int)obj.m->type;
    g.cr      = obj.m->color.x;
    g.cg      = obj.m->color.y;
    g.cb      = obj.m->color.z;
    g.param   = obj.m->param;
    return g;
}

// ---------------------------------------------------------------------------
// MetalRenderer
// ---------------------------------------------------------------------------

namespace util {

MetalRenderer::MetalRenderer(const scene::Scene& scn, const RenderParameters& p)
    : impl(std::make_unique<Impl>()), width(p.screenWidth), height(p.screenHeight)
{
    // --- Device & queue ---
    impl->device = MTLCreateSystemDefaultDevice();
    if (!impl->device) {
        std::cerr << "[MetalRenderer] No Metal device found\n";
        return;
    }
    impl->queue = [impl->device newCommandQueue];

    // --- Load and runtime-compile Metal shader source ---
    NSString* shaderPath = [execDir() stringByAppendingPathComponent:@"pathtracer.metal"];
    NSError*  err        = nil;
    NSString* src = [NSString stringWithContentsOfFile:shaderPath
                                              encoding:NSUTF8StringEncoding
                                                 error:&err];
    if (!src) {
        std::cerr << "[MetalRenderer] Cannot read shader at "
                  << [shaderPath UTF8String] << ": "
                  << [[err localizedDescription] UTF8String] << "\n";
        return;
    }
    std::cout << "[MetalRenderer] Compiling shader (first run may take a moment)...\n";
    MTLCompileOptions* opts = [[MTLCompileOptions alloc] init];
    id<MTLLibrary> lib = [impl->device newLibraryWithSource:src options:opts error:&err];
    if (!lib) {
        std::cerr << "[MetalRenderer] Shader compile error: "
                  << [[err localizedDescription] UTF8String] << "\n";
        return;
    }

    id<MTLFunction> fn = [lib newFunctionWithName:@"pathtrace"];
    impl->pipeline = [impl->device newComputePipelineStateWithFunction:fn error:&err];
    if (!impl->pipeline) {
        std::cerr << "[MetalRenderer] Pipeline error: "
                  << [[err localizedDescription] UTF8String] << "\n";
        return;
    }

    // --- Scene buffer ---
    const auto& objects = scn.getObjects();
    std::vector<GPUObject> gpuObjs;
    gpuObjs.reserve(objects.size());
    for (const auto& obj : objects)
        gpuObjs.push_back(toGPUObject(obj));

    impl->objectsBuf = [impl->device newBufferWithBytes:gpuObjs.data()
                                                 length:gpuObjs.size() * sizeof(GPUObject)
                                                options:MTLResourceStorageModeShared];

    // --- Camera / render params buffer ---
    // Replicate the camera setup from Render::Render()
    vec3 camPos = p.cameraPos;
    vec3 dir    = normalize(p.cameraLookAt - camPos);
    vec3 right  = normalize(cross(dir, p.worldUp));
    vec3 up     = normalize(cross(right, dir));

    float32 vHalf  = std::tan(degToRad(p.vfov * 0.5f)) * p.focalLength;
    float32 vWidth = vHalf * float32(width) / float32(height);

    vec3 deltaW   = right * (2.0f * vWidth  / float32(width));
    vec3 deltaH   = up    * (2.0f * vHalf   / float32(height));
    vec3 origin   = camPos + dir * p.focalLength
                    - right * vWidth - up * vHalf
                    + deltaW * 0.5f + deltaH * 0.5f;

    GPURenderParams rp = {};
    rp.width          = width;
    rp.height         = height;
    rp.samplesPerPixel = std::max(1, p.samplesPerPixel);
    rp.maxBounces     = p.maxBounces;
    rp.camPosX = camPos.x; rp.camPosY = camPos.y; rp.camPosZ = camPos.z;
    rp.originX = origin.x; rp.originY = origin.y; rp.originZ = origin.z;
    rp.deltaWX = deltaW.x; rp.deltaWY = deltaW.y; rp.deltaWZ = deltaW.z;
    rp.deltaHX = deltaH.x; rp.deltaHY = deltaH.y; rp.deltaHZ = deltaH.z;
    rp.objectCount = (int)gpuObjs.size();

    impl->paramsBuf = [impl->device newBufferWithBytes:&rp
                                                length:sizeof(GPURenderParams)
                                               options:MTLResourceStorageModeShared];

    // --- Output texture ---
    MTLTextureDescriptor* desc =
        [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA32Float
                                                          width:width
                                                         height:height
                                                      mipmapped:NO];
    desc.usage        = MTLTextureUsageShaderWrite | MTLTextureUsageShaderRead;
    desc.storageMode  = MTLStorageModeShared;
    impl->outTexture  = [impl->device newTextureWithDescriptor:desc];

    impl->width  = width;
    impl->height = height;

    std::cout << "[MetalRenderer] Ready: "
              << objects.size() << " objects, "
              << rp.samplesPerPixel << " spp, "
              << rp.maxBounces << " max bounces\n";
}

MetalRenderer::~MetalRenderer() = default;

void MetalRenderer::render() {
    if (!impl->pipeline) return;

    id<MTLCommandBuffer>         cmd     = [impl->queue commandBuffer];
    id<MTLComputeCommandEncoder> encoder = [cmd computeCommandEncoder];

    [encoder setComputePipelineState:impl->pipeline];
    [encoder setBuffer:impl->objectsBuf offset:0 atIndex:0];
    [encoder setBuffer:impl->paramsBuf  offset:0 atIndex:1];
    [encoder setTexture:impl->outTexture atIndex:0];

    // 16×16 threadgroup; Metal clips threads that fall outside the texture
    MTLSize tg   = MTLSizeMake(16, 16, 1);
    MTLSize grid = MTLSizeMake((NSUInteger)width, (NSUInteger)height, 1);
    [encoder dispatchThreads:grid threadsPerThreadgroup:tg];

    [encoder endEncoding];
    [cmd commit];
    [cmd waitUntilCompleted];
}

void MetalRenderer::save(std::string filepath) const {
    if (!impl->outTexture) return;

    int w = impl->width, h = impl->height;
    std::vector<float> pixels(w * h * 4);
    [impl->outTexture getBytes:pixels.data()
                   bytesPerRow:w * 4 * sizeof(float)
                    fromRegion:MTLRegionMake2D(0, 0, w, h)
                   mipmapLevel:0];

    Image img(w, h);
    for (int i = 0; i < w * h; i++) {
        float r = pixels[i * 4 + 0];
        float g = pixels[i * 4 + 1];
        float b = pixels[i * 4 + 2];
        // Gamma correction already applied in shader; just scale to [0,255]
        img.set(i, Pixel(
            static_cast<m3d::uint8>(std::min(r, 1.0f) * 255.0f),
            static_cast<m3d::uint8>(std::min(g, 1.0f) * 255.0f),
            static_cast<m3d::uint8>(std::min(b, 1.0f) * 255.0f)
        ));
    }
    img.save(filepath);
}

} // namespace util

#endif // __APPLE__
