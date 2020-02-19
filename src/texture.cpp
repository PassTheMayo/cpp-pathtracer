#include <algorithm>
#include "texture.h"

Texture::Texture()
{
    image = nullptr;
    width = 0;
    height = 0;
}

Texture::Texture(char *file)
{
    png::image<png::rgb_pixel> img(file);
    image = &img;
    width = img.get_width();
    height = img.get_height();
}

Color Texture::getColorAt(Vector3 uv)
{
    return getColorAt(uv.x, uv.y);
}

Color Texture::getColorAt(double u, double v)
{
    int u0 = std::max(std::min(u * double(width), double(width)), 0.0);
    int v0 = std::max(std::min(v * double(height), double(height)), 0.0);

    return image->get_pixel(u0, v0);
}