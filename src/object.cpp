#include "object.h"

Object::Object() {}

double Object::calculateIntersection(Ray *ray)
{
    return -1;
}

Vector3 Object::calculateNormal(Vector3 collisionPoint)
{
    return Vector3(0.0, 1.0, 0.0);
}

Material Object::getMaterial()
{
    return Material(0.0, 0.0, 0.0, Color(0.0, 0.0, 0.0));
}