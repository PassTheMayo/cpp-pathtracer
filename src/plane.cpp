#include <iostream>
#include "plane.h"

Plane::Plane()
{
    position = Vector3(0.0, 0.0, 0.0);
    normal = Vector3(0.0, 1.0, 0.0);
    material = Material(0.0, 0.0, 0.0, Color(0.0, 0.0, 0.0));
}

Plane::Plane(Vector3 position, Vector3 normal, Material material)
{
    this->position = position;
    this->normal = normal;
    this->material = material;
}

double Plane::calculateIntersection(Ray *ray)
{
    return normal.dot(ray->origin - position) / -ray->direction.dot(normal);
}

Vector3 Plane::calculateNormal(Vector3 collisionPoint)
{
    return normal;
}

Material Plane::getMaterial()
{
    return material;
}