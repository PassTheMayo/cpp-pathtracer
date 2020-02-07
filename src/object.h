#pragma once

#include "ray.h"
#include "material.h"

class Object
{
public:
    Object();
    double calculateIntersection(Ray *ray);
    Vector3 calculateNormal(Vector3 collisionPoint);
    Material getMaterial();
};