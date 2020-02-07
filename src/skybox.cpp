#include <math.h>
#include "skybox.h"

Vector3 up = Vector3(0.0, 1.0, 0.0);

Skybox::Skybox()
{
    this->topColor = Color();
    this->sideColor = Color();
    this->bottomColor = Color();
    this->intensity = 0.0;
}

Skybox::Skybox(Color topColor, Color sideColor, Color bottomColor, double intensity)
{
    this->topColor = topColor;
    this->sideColor = sideColor;
    this->bottomColor = bottomColor;
    this->intensity = intensity;
}

Color Skybox::getColor(Vector3 rayDirection)
{
    double dot = up.dot(rayDirection);

    if (dot < 0)
    {
        return sideColor.interpolate(bottomColor, abs(dot));
    }

    return sideColor.interpolate(topColor, dot);
}