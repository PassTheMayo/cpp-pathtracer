#include <algorithm>
#include "texture.h"

Texture::Texture() {}

Texture::Texture(char *file)
{
    image = png::image<png::rgb_pixel>(file);
    width = image.get_width();
    height = image.get_height();
}

Color Texture::getColorAt(Vector3 uv)
{
    return getColorAt(uv.x, uv.y);
}

Color Texture::getColorAt(double u, double v)
{
    int u0 = std::max(std::min(u * double(width), double(width)), 0.0);
    int v0 = std::max(std::min(v * double(height), double(height)), 0.0);

    // std::cout << u << ", " << v << std::endl;

    return image.get_pixel(u0, v0);
}