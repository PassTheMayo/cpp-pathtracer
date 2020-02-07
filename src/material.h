#pragma once

#include "color.h"

class Material
{
public:
    double reflectivity;
    double diffuse;
    double emittance;
    Color color;

    Material();
    Material(double reflectivity, double diffuse, double emittance, Color color);
};