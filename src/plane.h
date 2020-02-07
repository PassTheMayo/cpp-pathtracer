#pragma once

#include "object.h"
#include "vector.h"
#include "material.h"

class Plane : public Object
{
public:
    Vector3 position;
    Vector3 normal;
    Material material;

    Plane();
    Plane(Vector3 position, Vector3 normal, Material material);
    double calculateIntersection(Ray *ray);
    Vector3 calculateNormal(Vector3 collisionPoint);
    Material getMaterial();
};