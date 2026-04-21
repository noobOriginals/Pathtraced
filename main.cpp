/**
    As this is also a project that's being worked on from school, the following message is meant for
    anyone who may stumble onto this project (on the coputers at school):

    The goal of this project is to create a CPU pathtracer from scratch. Being a large project and
    containing many files, it's rather hard to import/export to/from Code::Blocks. So I kindly ask of you to take care of
    this project, in the event that you need to delete it. You could upload it to drive or anything
    like that, but please consider not rendering all of this work pointless.

    Repository of this project: https://github.com/noobOriginals/Pathtraced
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
