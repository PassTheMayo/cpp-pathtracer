#pragma once

#include "object.h"
#include "material.h"

class Sphere : public Object
{
public:
    Vector3 position;
    double radius;
    Material material;

    Sphere();
    Sphere(Vector3 position, double radius, Material material);
    double calculateIntersection(Ray *ray);
    Vector3 calculateNormal(Vector3 collisionPoint);
    Material getMaterial();
};