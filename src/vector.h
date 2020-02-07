#pragma once

#include <array>

class Vector3
{
public:
    double x;
    double y;
    double z;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(double x, double y, double z);
    Vector3 add(Vector3 v2);
    Vector3 add(float scalar);
    Vector3 add(double scalar);
    Vector3 subtract(Vector3 v2);
    Vector3 subtract(float scalar);
    Vector3 subtract(double scalar);
    Vector3 multiply(Vector3 v2);
    Vector3 multiply(float scalar);
    Vector3 multiply(double scalar);
    Vector3 multiply(std::array<std::array<double, 3>, 3> matrix3);
    Vector3 divide(Vector3 v2);
    Vector3 divide(float scalar);
    Vector3 divide(double scalar);
    double magnitude();
    double distance(Vector3 v2);
    double dot(Vector3 v2);
    Vector3 cross(Vector3 v2);
    Vector3 interpolate(Vector3 v2, float scalar);
    Vector3 interpolate(Vector3 v2, double scalar);
    Vector3 normalize();
    Vector3 operator+(Vector3 v2);
    Vector3 operator+(float scalar);
    Vector3 operator+(double scalar);
    Vector3 operator-(Vector3 v2);
    Vector3 operator-(float scalar);
    Vector3 operator-(double scalar);
    Vector3 operator*(Vector3 v2);
    Vector3 operator*(float scalar);
    Vector3 operator*(double scalar);
    Vector3 operator/(Vector3 v2);
    Vector3 operator/(float scalar);
    Vector3 operator/(double scalar);
};