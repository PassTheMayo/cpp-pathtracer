#pragma once

#include "ray.h"
#include "material.h"

class Object
{
public:
    Object();
    virtual double calculateIntersection(Ray *ray);
    virtual Vector3 calculateNormal(Vector3 collisionPoint);
    virtual Material getMaterial();
};