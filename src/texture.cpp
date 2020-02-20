#include <algorithm>
#include "texture.h"

Texture::Texture() {}

Texture::~Texture() {}

Texture::Texture(std::string file, int width, int height)
{
    png::image<png::rgb_pixel> img(file);

    this->width = width;
    this->height = height;
    this->image = std::vector<Color>(width * height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image.at(x + y * width) = img.get_pixel(x, y);
        }
    }
}

Color Texture::getColorAt(Vector3 uv)
{
    return getColorAt(uv.x, uv.y);
}

Color Texture::getColorAt(double u, double v)
{
    int x = std::max(std::min(u, 1.0), 0.0) * double(width - 1);
    int y = std::max(std::min(v, 1.0), 0.0) * double(height - 1);

    return image.at(x + y * width);
}