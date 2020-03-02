#include <math.h>
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

Vector3 Ray::reflect(Vector3 normal)
{
    return (direction - normal * direction.dot(normal) * 2.0).normalize();
}

bool Ray::refract(Vector3 normal, double ior, Vector3 *refractedDirection)
{
    if (direction.dot(normal) > 0)
    {
        normal = normal * -1.0;
    }
    else
    {
        ior = 1.0 / ior;
    }

    Vector3 uv = direction.normalize();

    double dt = uv.dot(normal);
    double discriminant = 1.0 - ior * ior * (1 - dt * dt);

    if (discriminant <= 0)
    {
        return false;
    }

    *refractedDirection = ((uv - normal * dt) * ior - normal * sqrt(discriminant)).normalize();

    return true;
}