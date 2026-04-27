#include "render.hpp"

// Render

Render::Render(int32 width, int32 height, float32 verticalFOV) {
    viewport = Viewport(width, height, degToRad(verticalFOV));
    camera = Camera(Vec3(), Vec3(), viewport);
    image = Image(width, height);
}

void Render::begin() const {
    done = false;

    int32 width = viewport.getScreenWidth();
    int32 height = viewport.getScreenHeight();

    Vec3 supersampleDelta = camera.getPixelDelta() / Vec3(supersamplesX + 1, supersamplesY + 1, 1.0);

    Pixel* pixels = image.getPixels(nullptr);

    for (int32 y = 0; y < height; y++) {
        for (int32 x = 0; x < width; x++) {
            Vec3 color = Vec3(0.0);
            if (supersampling) {
                Vec3 supersampleOrigin = camera.getPixel(x, y) - camera.getPixelDelta() * 0.5 + supersampleDelta;
                for (int32 sy = 0; sy < supersamplesY; sy++) {
                    for (int32 sx = 0; sx < supersamplesX; sx++) {
                        Vec3 pixel = supersampleOrigin + supersampleDelta * Vec3(sx, sy, 0.0);
                        Ray ray = Ray(camera.getPos(), normalize(pixel - camera.getPos()));
                        color += raytrace(ray);
                    }
                }
                color /= supersamplesX * supersamplesY;
            } else {
                color = raytrace(Ray(camera.getPos(), normalize(camera.getPixel(x, y) - camera.getPos())));
            }
            pixels[y * width + x] = Pixel(color);
        }
    }

    done = true;
}

const bool& Render::isDone() const {
    return done;
}

void Render::setCameraPos(Vec3 pos) {
    camera.setPosition(pos);
    camera.computeValues();
}

void Render::setCameraLookat(Vec3 lookat) {
    camera.setLookat(lookat);
    camera.computeValues();
}

void Render::setCameraPosAndLookat(Vec3 pos, Vec3 lookat) {
    camera.setPosition(pos);
    camera.setLookat(lookat);
    camera.computeValues();
}

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

void Render::save(std::string filename) const {
    image.save(filename);
}

const Image& Render::getImage() const {
    return image;
}

void Render::setRaytraceCallback(RaytraceCallback rt) {
    raytrace = rt;
}
