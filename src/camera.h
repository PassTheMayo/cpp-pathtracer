#pragma once

#include "ray.h"
#include "vector.h"
#include "rotation.h"

class Camera
{
public:
    Vector3 position;
    Rotation rotation;
    double fov;
    double aspectRatio;
    int maxBounces;

    Camera(Vector3 position, Rotation rotation, double aspectRatio, double fov, int maxBounces);
    Ray getRay(double x, double y);
};