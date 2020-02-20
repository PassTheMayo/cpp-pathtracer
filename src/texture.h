#pragma once

#include <png++/png.hpp>
#include "vector.h"
#include "color.h"

class Texture
{
public:
    std::vector<Color> image;
    int width = 0;
    int height = 0;

    Texture();
    ~Texture();
    Texture(std::string file, int width, int height);
    Color getColorAt(Vector3 uv);
    Color getColorAt(double u, double v);
};