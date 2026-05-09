#ifndef UTIL_GPU_SCENE_HPP
#define UTIL_GPU_SCENE_HPP

// Flat, alignment-safe structs shared between CPU (metal_render.mm) and the Metal shader.
// All members are int or float (4 bytes each) — no padding surprises.

struct GPUObject {
    int   type;       // 0=sphere  1=triangle  2=quad
    float d[12];      // sphere:   d[0..2]=center  d[3]=radius
                      // triangle: d[0..2]=a  d[3..5]=b  d[6..8]=c
                      // quad:     d[0..2]=center  d[3..5]=u  d[6..8]=v
    int   matType;    // 0=diffuse  1=metal  2=dielectric
    float cr, cg, cb; // albedo
    float param;      // metal: roughness  dielectric: index of refraction
};

struct GPURenderParams {
    int   width, height;
    int   samplesPerPixel, maxBounces;
    float camPosX, camPosY, camPosZ;
    float originX, originY, originZ;   // pixel (0,0) centre in world space
    float deltaWX, deltaWY, deltaWZ;   // world-space step per pixel in X
    float deltaHX, deltaHY, deltaHZ;   // world-space step per pixel in Y
    int   objectCount;
    int   pad;
};

#endif // UTIL_GPU_SCENE_HPP
