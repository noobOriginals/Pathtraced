#include "render.hpp"

using namespace m3d;

// Render

Render::Render(int32 width, int32 height, float32 verticalFOV) {
    viewport = Viewport(width, height, degToRad(verticalFOV));
    camera = Camera(vec3(), vec3(), viewport);
    image = Image(width, height);
}

void Render::begin() const {
    done = false;

    int32 width = viewport.getScreenWidth();
    int32 height = viewport.getScreenHeight();

    vec3 supersampleDeltaX = camera.getPixelDeltaX() / (supersamplesX + 1);
    vec3 supersampleDeltaY = camera.getPixelDeltaY() / (supersamplesY + 1);

    Pixel* pixels = image.getPixels(nullptr);

    for (int32 y = 0; y < height; y++) {
        for (int32 x = 0; x < width; x++) {
            vec3 color = vec3(0.0);
            if (supersampling) {
                vec3 supersampleOrigin = camera.getPixel(x, y) - camera.getPixelDeltaX() * 0.5 + supersampleDeltaX - camera.getPixelDeltaY() * 0.5 + supersampleDeltaY;
                for (int32 sy = 0; sy < supersamplesY; sy++) {
                    for (int32 sx = 0; sx < supersamplesX; sx++) {
                        vec3 pixel = supersampleOrigin + supersampleDeltaX * sx + supersampleDeltaY * sy;
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
