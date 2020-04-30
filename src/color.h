#pragma once

#include <png++/png.hpp>
#include "vector.h"

class Color
{
public:
    double r;
    double g;
    double b;

    Color();
    Color(png::rgb_pixel pixel);
    Color(Vector3 vector);
    Color(float r, float g, float b);
    Color(double r, double g, double b);
    Color(double v);
    Color add(Color color);
    Color add(float value);
    Color add(double value);
    Color add(float r, float g, float b);
    Color add(double r, double g, double b);
    Color subtract(Color color);
    Color subtract(float value);
    Color subtract(double value);
    Color subtract(float r, float g, float b);
    Color subtract(double r, double g, double b);
    Color multiply(Color color);
    Color multiply(float value);
    Color multiply(double value);
    Color multiply(float r, float g, float b);
    Color multiply(double r, double g, double b);
    Color divide(Color color);
    Color divide(float value);
    Color divide(double value);
    Color divide(float r, float g, float b);
    Color divide(double r, double g, double b);
    Color clamp();
    Color interpolate(Color c2, double scalar);
    double magnitude();
    png::rgba_pixel toRGBAPixel();
    Color operator+(Color color);
    Color operator+(float value);
    Color operator+(double value);
    Color operator-(Color color);
    Color operator-(float value);
    Color operator-(double value);
    Color operator*(Color color);
    Color operator*(float value);
    Color operator*(double value);
    Color operator/(Color color);
    Color operator/(float value);
    Color operator/(double value);
    friend std::ostream &operator<<(std::ostream &os, const Color &dt);
};