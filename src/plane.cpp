#include <iostream>
#include "plane.h"

Plane::Plane()
{
    position = Vector3();
    normal = Vector3();
    material = Material();
}

Plane::Plane(Vector3 position, Vector3 normal, Material material)
{
    this->position = position;
    this->normal = normal;
    this->material = material;
}

Plane::~Plane() {}

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