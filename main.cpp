/**
    To whom may stumble onto this project: ..
 */

// Std includes
#include <iostream>

// Local includes
#include "image.hpp"

int main() {
    int32 width = 800;
    int32 height = 600;

    Image img(width, height);
    Pixel* pixels = img.getPixles(nullptr);

    for (int32 y = 0; y < height; y++) {
        for (int32 x = 0; x < width; x++) {
            pixels[y * width + x] = Pixel(Vec3((float32)x / width, (float32)y / height, (float32)(x + y) / (width + height)));
        }
    }

    img.save("render.bmp");
    return 0;
}