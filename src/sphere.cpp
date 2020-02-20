#include <math.h>
#include "util.h"
#include "sphere.h"
#include "material.h"

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

Sphere::~Sphere() {}

double Sphere::calculateIntersection(Ray ray)
{
    Vector3 directionToCenter = position.subtract(ray.origin);
    double midpointDistance = directionToCenter.dot(ray.direction);
    double discriminant = (radius * radius) - directionToCenter.dot(directionToCenter) + (midpointDistance * midpointDistance);

    if (discriminant < 0)
    {
        return -1;
    }

    double dist = midpointDistance - sqrt(discriminant);

    if (dist > EPSILON)
    {
        return dist;
    }

    double dist2 = midpointDistance + sqrt(discriminant);

    if (dist2 > EPSILON)
    {
        return dist;
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

Vector3 Sphere::calculateUVCoordinates(Vector3 collisionPoint, Vector3 normal)
{
    return Vector3(atan2(normal.x, normal.z) / (2 * M_PI) + 0.5, normal.y * 0.5 + 0.5, 0.0);
}