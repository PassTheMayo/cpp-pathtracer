#include "material.h"

Material::Material()
{
    this->reflectivity = 0;
    this->diffuse = 0;
    this->emittance = 0;
    this->color = Color();
}

Material::Material(double reflectivity, double diffuse, double emittance, Color color)
{
    this->reflectivity = reflectivity;
    this->diffuse = diffuse;
    this->emittance = emittance;
    this->color = color;
}