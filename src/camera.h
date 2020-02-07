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
    int maxBounces;

    Camera(Vector3 position, Rotation rotation, double fov, int maxBounces);
    Ray getRay(double x, double y, double aspectRatio);
};