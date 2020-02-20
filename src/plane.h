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
    ~Plane();
    double calculateIntersection(Ray ray);
    Vector3 calculateNormal(Vector3 collisionPoint);
    Material getMaterial();
    Vector3 calculateUVCoordinates(Vector3 collisionPoint, Vector3 normal);
};