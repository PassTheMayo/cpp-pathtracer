#include <math.h>
#include <algorithm>
#include "color.h"

Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(png::rgb_pixel pixel)
{
    this->r = pixel.red;
    this->g = pixel.green;
    this->b = pixel.blue;
}

Color::Color(Vector3 vector)
{
    this->r = vector.x * 255;
    this->g = vector.y * 255;
    this->b = vector.z * 255;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::add(Color color)
{
    return Color(r + color.r, g + color.g, b + color.b);
}

Color Color::add(float value)
{
    return Color(r + value, g + value, b + value);
}

Color Color::add(double value)
{
    return Color(r + value, g + value, b + value);
}

Color Color::add(float r, float g, float b)
{
    return Color(this->r + r, this->g + g, this->b + b);
}

Color Color::add(double r, double g, double b)
{
    return Color(this->r + r, this->g + g, this->b + b);
}

Color Color::subtract(Color color)
{
    return Color(r - color.r, g - color.g, b - color.b);
}

Color Color::subtract(float value)
{
    return Color(r - value, g - value, b - value);
}

Color Color::subtract(double value)
{
    return Color(r - value, g - value, b - value);
}

Color Color::subtract(float r, float g, float b)
{
    return Color(this->r - r, this->g - g, this->b - b);
}

Color Color::subtract(double r, double g, double b)
{
    return Color(this->r - r, this->g - g, this->b - b);
}

Color Color::multiply(Color color)
{
    return Color(r * (double(color.r) / 255), g * (double(color.g) / 255), b * (double(color.b) / 255));
}

Color Color::multiply(float value)
{
    return Color(r * value, g * value, b * value);
}

Color Color::multiply(double value)
{
    return Color(r * value, g * value, b * value);
}

Color Color::multiply(float r, float g, float b)
{
    return Color(this->r * (r / 255), this->g * (g / 255), this->b * (b / 255));
}

Color Color::multiply(double r, double g, double b)
{
    return Color(this->r * (r / 255), this->g * (g / 255), this->b * (b / 255));
}

Color Color::divide(Color color)
{
    return Color(r / color.r, g / color.g, b / color.b);
}

Color Color::divide(float value)
{
    return Color(r / value, g / value, b / value);
}

Color Color::divide(double value)
{
    return Color(r / value, g / value, b / value);
}

Color Color::divide(float r, float g, float b)
{
    return Color(this->r / r, this->g / g, this->b / b);
}

Color Color::divide(double r, double g, double b)
{
    return Color(this->r / r, this->g / g, this->b / b);
}

Color Color::clamp()
{
    return Color(std::max(std::min(r, 255.0), 0.0), std::max(std::min(g, 255.0), 0.0), std::max(std::min(b, 255.0), 0.0));
}

Color Color::interpolate(Color c2, double scalar)
{
    return Color(r + (c2.r - r) * scalar, g + (c2.g - g) * scalar, b + (c2.b - b) * scalar);
}

double Color::magnitude()
{
    return (r + g + b) / (255 * 3);
}

png::rgba_pixel Color::toRGBAPixel()
{
    return png::rgba_pixel(r, g, b, 255);
}

Color Color::operator+(Color color)
{
    return add(color);
}

Color Color::operator+(float value)
{
    return add(value);
}

Color Color::operator+(double value)
{
    return add(value);
}

Color Color::operator-(Color color)
{
    return subtract(color);
}

Color Color::operator-(float value)
{
    return subtract(value);
}

Color Color::operator-(double value)
{
    return subtract(value);
}

Color Color::operator*(Color color)
{
    return multiply(color);
}

Color Color::operator*(float value)
{
    return multiply(value);
}

Color Color::operator*(double value)
{
    return multiply(value);
}

Color Color::operator/(Color color)
{
    return divide(color);
}

Color Color::operator/(float value)
{
    return divide(value);
}

Color Color::operator/(double value)
{
    return divide(value);
}

std::ostream &operator<<(std::ostream &os, const Color &c)
{
    os << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";

    return os;
}