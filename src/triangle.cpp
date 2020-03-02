#include <math.h>
#include "util.h"
#include "triangle.h"

Triangle::Triangle()
{
    this->vertex1 = Vector3();
    this->vertex2 = Vector3();
    this->vertex3 = Vector3();
    this->material = Material();
}

Triangle::Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3, Material material)
{
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->vertex3 = vertex3;
    this->material = material;
}

Triangle::~Triangle() {}

double Triangle::calculateIntersection(Ray ray)
{
    Vector3 edge1 = vertex2 - vertex1;
    Vector3 edge2 = vertex3 - vertex1;
    Vector3 h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON)
    {
        return -1;
    }

    double f = 1.0 / a;
    Vector3 s = ray.origin - vertex1;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
    {
        return -1;
    }

    Vector3 q = s.cross(edge1);
    double v = f * ray.direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
    {
        return -1;
    }

    return f * edge2.dot(q);
}

Vector3 Triangle::calculateNormal(Vector3 collisionPoint)
{
    return (vertex2 - vertex1).cross(vertex3 - vertex1).normalize();
}

Material Triangle::getMaterial()
{
    return material;
}

Vector3 Triangle::calculateUVCoordinates(Vector3 collisionPoint, Vector3 normal)
{
    Vector3 v0 = vertex2 - vertex1;
    Vector3 v1 = vertex3 - vertex1;
    Vector3 v2 = collisionPoint - vertex1;

    double d00 = v0.dot(v0);
    double d01 = v0.dot(v1);
    double d11 = v1.dot(v1);
    double d20 = v2.dot(v0);
    double d21 = v2.dot(v1);
    double denom = d00 * d11 - d01 * d01;

    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0f - v - w;

    return Vector3(u, w, 0.0);
}