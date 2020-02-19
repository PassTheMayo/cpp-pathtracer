#pragma once

#include <png++/png.hpp>
#include "vector.h"
#include "color.h"

class Texture
{
public:
    png::image<png::rgb_pixel> *image = nullptr;
    size_t width;
    size_t height;

    Texture();
    Texture(char *file);
    Color getColorAt(Vector3 uv);
    Color getColorAt(double u, double v);
};