#include "triangle.h"

const double EPSILON = 0.00001;

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

double Triangle::calculateIntersection(Ray *ray)
{
    Vector3 edge1 = vertex2 - vertex1;
    Vector3 edge2 = vertex3 - vertex1;
    Vector3 h = ray->direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON)
    {
        return -1;
    }

    double f = 1.0 / a;
    Vector3 s = ray->origin - vertex1;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
    {
        return -1;
    }

    Vector3 q = s.cross(edge1);
    double v = f * ray->direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
    {
        return -1;
    }

    return f * edge2.dot(q);
}

Vector3 Triangle::calculateNormal(Vector3 collisionPoint)
{
    return vertex2.subtract(vertex1).cross(vertex3 - vertex1);
}

Material Triangle::getMaterial()
{
    return material;
}