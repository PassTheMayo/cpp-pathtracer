#pragma once

#include "object.h"
#include "vector.h"

class Triangle : public Object
{
public:
    Vector3 vertex1;
    Vector3 vertex2;
    Vector3 vertex3;
    Material material;

    Triangle();
    Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3, Material material);
    ~Triangle();
    double calculateIntersection(Ray ray);
    Vector3 calculateNormal(Vector3 collisionPoint);
    Material getMaterial();
    Vector3 calculateUVCoordinates(Vector3 collisionPoint, Vector3 normal);
};