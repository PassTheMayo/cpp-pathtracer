#pragma once

#include "color.h"
#include "texture.h"

class Material
{
public:
    double metallic;
    double roughness;
    double emittance;
    double transmission;
    double ior;
    Color color;
    Texture *texture = nullptr;

    Material();
    Material(double metallic, double roughness, double emittance, double transmission, double ior, Color color, Texture *texture);
};