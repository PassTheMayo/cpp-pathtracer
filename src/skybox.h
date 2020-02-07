#pragma once

#include "color.h"
#include "vector.h"

class Skybox
{
public:
    Color topColor;
    Color sideColor;
    Color bottomColor;
    double intensity;

    Skybox();
    Skybox(Color topColor, Color sideColor, Color bottomColor, double intensity);
    Color getColor(Vector3 rayDirection);
};