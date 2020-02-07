#include <math.h>
#include "vector.h"

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::add(Vector3 v2)
{
    return Vector3(x + v2.x, y + v2.y, z + v2.z);
}

Vector3 Vector3::add(float scalar)
{
    return Vector3(x + scalar, y + scalar, z + scalar);
}

Vector3 Vector3::add(double scalar)
{
    return Vector3(x + scalar, y + scalar, z + scalar);
}

Vector3 Vector3::subtract(Vector3 v2)
{
    return Vector3(x - v2.x, y - v2.y, z - v2.z);
}

Vector3 Vector3::subtract(float scalar)
{
    return Vector3(x - scalar, y - scalar, z - scalar);
}

Vector3 Vector3::subtract(double scalar)
{
    return Vector3(x - scalar, y - scalar, z - scalar);
}

Vector3 Vector3::multiply(Vector3 v2)
{
    return Vector3(x * v2.x, y * v2.y, z * v2.z);
}

Vector3 Vector3::multiply(float scalar)
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::multiply(double scalar)
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::multiply(std::array<std::array<double, 3>, 3> matrix3)
{
    Vector3 res = Vector3(0.0, 0.0, 0.0);

    res.x += this->x * matrix3[0][0];
    res.x += this->y * matrix3[0][1];
    res.x += this->z * matrix3[0][2];

    res.y += this->x * matrix3[1][0];
    res.y += this->y * matrix3[1][1];
    res.y += this->z * matrix3[1][2];

    res.z += this->x * matrix3[2][0];
    res.z += this->y * matrix3[2][1];
    res.z += this->z * matrix3[2][2];

    return res;
}

Vector3 Vector3::divide(Vector3 v2)
{
    return Vector3(x / v2.x, y / v2.y, z / v2.z);
}

Vector3 Vector3::divide(float scalar)
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::divide(double scalar)
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

double Vector3::magnitude()
{
    return sqrt(x * x + y * y + z * z);
}

double Vector3::distance(Vector3 v2)
{
    double a = v2.x - x;
    double b = v2.y - y;
    double c = v2.z - z;

    return sqrt(a * a + b * b + c * c);
}

double Vector3::dot(Vector3 v2)
{
    return x * v2.x + y * v2.y + z * v2.z;
}

Vector3 Vector3::cross(Vector3 v2)
{
    return Vector3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
}

Vector3 Vector3::interpolate(Vector3 v2, float scalar)
{
    return Vector3(x + (v2.x - x) * scalar, y + (v2.y - y) * scalar, z + (v2.z - z) * scalar);
}

Vector3 Vector3::interpolate(Vector3 v2, double scalar)
{
    return Vector3(x + (v2.x - x) * scalar, y + (v2.y - y) * scalar, z + (v2.z - z) * scalar);
}

Vector3 Vector3::normalize()
{
    return divide(magnitude());
}

Vector3 Vector3::operator+(Vector3 v2)
{
    return add(v2);
}

Vector3 Vector3::operator+(float scalar)
{
    return add(scalar);
}

Vector3 Vector3::operator+(double scalar)
{
    return add(scalar);
}

Vector3 Vector3::operator-(Vector3 v2)
{
    return subtract(v2);
}

Vector3 Vector3::operator-(float scalar)
{
    return subtract(scalar);
}

Vector3 Vector3::operator-(double scalar)
{
    return subtract(scalar);
}

Vector3 Vector3::operator*(Vector3 v2)
{
    return multiply(v2);
}

Vector3 Vector3::operator*(float scalar)
{
    return multiply(scalar);
}

Vector3 Vector3::operator*(double scalar)
{
    return multiply(scalar);
}

Vector3 Vector3::operator/(Vector3 v2)
{
    return divide(v2);
}

Vector3 Vector3::operator/(float scalar)
{
    return divide(scalar);
}

Vector3 Vector3::operator/(double scalar)
{
    return divide(scalar);
}