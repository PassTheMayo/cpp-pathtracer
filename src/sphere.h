#pragma once

#include "object.h"
#include "material.h"

class Sphere : public Object
{
public:
    Vector3 position;
    double radius;
    Material material;

    Sphere(Vector3 position, double radius, Material material);
    double calculateIntersection(Ray ray);
    double calculateNormal(Vector3 collisionPoint);
};