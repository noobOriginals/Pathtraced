# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and Run

```bash
# Configure (from project root)
cmake -S . -B build

# Build
cmake --build build

# Run (outputs render.bmp inside bin/)
./bin/Pathtraced
```

The `CopyResources` CMake target automatically copies `scenes/*.scn` files into `bin/` alongside the executable.

## Architecture Overview

The main rendering loop lives in `main.cpp`, which wires together scene construction, render configuration, and the chosen renderer. On Apple platforms `MetalRenderer` is used by default; on all others the CPU `Render` path runs.

### Rendering Pipeline

1. `SceneCreator` utilities build the scene (geometry + materials)
2. `Scene::save()` optionally serializes to a `.scn` file
3. **GPU (Apple)** — `MetalRenderer` serializes the scene into a flat `GPUObject` buffer, uploads it to the GPU, and dispatches `pathtrace` (one thread per pixel). The shader handles sampling, bouncing, and gamma correction, then writes `RGBA32Float` to a Metal texture. Pixels are read back and saved via `Image`.
4. **CPU (fallback)** — `Render` iterates pixels via tile-based multithreading, calls the user-supplied `raytrace()` callback per sample.
5. `Image::save()` writes a BMP.

`RenderParameters` controls resolution, camera (position, target, up, FOV), samples-per-pixel, max bounce depth, and tile-based multithreading (CPU path).

### Core Subsystems

| Subsystem | Location | Role |
|-----------|----------|------|
| Math library | `src/include/lib/m3d.hpp` | `vec2/3/4`, `mat3/4`, transforms — single-precision throughout |
| Ray / Hitpoint | `src/include/math/` | `Ray` (origin + dir), `Hitpoint` (t, position, normal, exit flag) |
| Geometry | `src/include/geometry/` | `Hittable` (abstract), `Sphere`, `Triangle` (Möller–Trumbore), `Quad` |
| Material | `src/include/material/` | `Material` (DIFFUSE / METAL / DIELECTRIC) + `ScatterResult` |
| Scene | `src/include/scene/` | `Scene` owns `Object`s (each pairs `Hittable*` + `Material*`); provides closest-hit query |
| CPU renderer | `src/include/util/render.hpp` | Pixel loop, supersampling, gamma correction, thread-tile dispatch |
| Metal renderer | `src/include/util/metal_render.hpp` | Apple-only; pimpl wrapping Metal API; reads `RenderParameters` + `Scene` |
| GPU structs | `src/include/util/gpu_scene.hpp` | `GPUObject` / `GPURenderParams` — flat structs shared by CPU upload and Metal shader |
| Metal shader | `src/shaders/pathtracer.metal` | Compute kernel: PRNG, all three intersection tests, all three material models |
| Scene builder | `src/include/util/scene_creator.hpp` | Grid, jittered-grid, and random generators for spheres/triangles/quads; mixed-material batches |

### Memory Ownership

`Scene` owns all `Object`s, which in turn own heap-allocated `Hittable*` and `Material*`. `SceneCreator::populateScene()` clones geometry and transfers heap-allocated material ownership to the scene — callers must not free those pointers.

### Material Model

- **DIFFUSE** — Lambertian; `color` is albedo, `param` unused  
- **METAL** — specular reflection; `param` is roughness/fuzz  
- **DIELECTRIC** — refraction + Fresnel (Schlick); `param` is index of refraction

### Adding New Geometry

1. Subclass `Hittable` in `src/include/geometry/`, implement `hit()`, `clone()`, `toString()`, and `getType()` (return the next unused int ≥ 3).
2. Add public coordinate getters (see `Sphere::getCenter()` / `getRadius()` for the pattern).
3. In `metal_render.mm::toGPUObject()`, add a `dynamic_cast` branch and pack the geometry into `g.d[]`.
4. In `pathtracer.metal`, add a `hit_<shape>()` function and a dispatch branch in `scene_hit()`.
5. Optionally add a template struct in `scene_creator.hpp` for bulk generation.

### Metal Shader Notes

- The shader is compiled at runtime by the Metal framework (`newLibraryWithSource:`); no Xcode is required.
- `bin/pathtracer.metal` is copied there at build time; rebuild after shader edits.
- `GPUObject.d[12]` packs all geometry; layout is documented in `gpu_scene.hpp`.
- The PRNG is xorshift32 seeded per `(pixel_x, pixel_y, sample_index)` — different seeds each sample give independent jitter.
