#include <algorithm>
#include "texture.h"

Texture::Texture() {}

Texture::Texture(char *file)
{
    png::image<png::rgb_pixel> img(file);
    img.read(file);

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
    return image->get_pixel(size_t(u) * width, size_t(v) * height);
}