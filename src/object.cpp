#include "object.h"

Object::Object() {}

double Object::calculateIntersection(Ray *ray)
{
    throw "Object::calculateIntersection() called";
}

Vector3 Object::calculateNormal(Vector3 collisionPoint)
{
    throw "Object::calculateNormal() called";
}

Material Object::getMaterial()
{
    throw "Object::getMaterial() called";
}

Vector3 Object::calculateUVCoordinates(Vector3 collisionPoint, Vector3 normal)
{
    throw "Object::calculateUVCoordinates() called";
}