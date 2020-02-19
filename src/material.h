#pragma once

#include "color.h"
#include "texture.h"

class Material
{
public:
    double reflectivity;
    double diffuse;
    double emittance;
    double transmission;
    double ior;
    Color color;
    Texture *texture = nullptr;

    Material();
    Material(double reflectivity, double diffuse, double emittance, double transmission, double ior, Color color, Texture *texture);
};