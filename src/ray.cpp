#include "ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
{
    this->origin = origin;
    this->direction = direction;
}

Vector3 Ray::across(double distance)
{
    return origin.add(direction.multiply(distance));
}