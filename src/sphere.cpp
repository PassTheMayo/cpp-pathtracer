#include <math.h>
#include "sphere.h"
#include "material.h"

const double EPSILON = 0.00001;

Sphere::Sphere()
{
    this->position = Vector3();
    this->radius = 0;
    this->material = Material();
}

Sphere::Sphere(Vector3 position, double radius, Material material)
{
    this->position = position;
    this->radius = radius;
    this->material = material;
}

double Sphere::calculateIntersection(Ray *ray)
{
    Vector3 directionToCenter = position.subtract(ray->origin);
    double midpointDistance = directionToCenter.dot(ray->direction);
    double midpointToCenter = directionToCenter.dot(directionToCenter);
    double discriminant = (radius * radius) - midpointToCenter + (midpointDistance * midpointDistance);

    if (discriminant < 0)
    {
        return -1;
    }

    if (midpointDistance - sqrt(discriminant) > EPSILON)
    {
        return midpointDistance - sqrt(discriminant);
    }

    if (midpointDistance + sqrt(discriminant) > EPSILON)
    {
        return midpointDistance + sqrt(discriminant);
    }

    return -1;
}

Vector3 Sphere::calculateNormal(Vector3 intersectionPoint)
{
    return intersectionPoint.subtract(position);
}

Material Sphere::getMaterial()
{
    return material;
}