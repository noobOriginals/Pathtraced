#ifndef IMAGE_HPP
#define IMAGE_HPP

// Std includes
#include <string>

// Local includes
#include "m3d.hpp"

struct Pixel {
    m3d::uint8 r, g, b;
    Pixel();
    Pixel(m3d::uint8 r, m3d::uint8 g, m3d::uint8 b);
    Pixel(m3d::vec3 v);
};

class Image {
public:
    Image() = default;
    Image(const Image& other);
    Image(m3d::int32 width, m3d::int32 height);
    ~Image();

    Pixel get(m3d::int32 x, m3d::int32 y) const;

    void set(m3d::int32 x, m3d::int32 y, Pixel p);
    void set(m3d::int32 i, Pixel p);
    void setPixels(m3d::int32 size, m3d::int32 offset, Pixel* pixels);

    void save(std::string filename) const;

    const m3d::int32& getWidth() const;
    const m3d::int32& getHeight() const;
    const m3d::int32& getSize() const;
    Pixel* getPixels(m3d::int32* size) const;

    void operator=(const Image& other);

private:
    Pixel* pixels;
    m3d::int32 width, height, size;
};

#endif // IMAGE_HPP