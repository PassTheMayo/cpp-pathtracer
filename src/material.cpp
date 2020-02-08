#include "material.h"

Material::Material()
{
    this->reflectivity = 0;
    this->diffuse = 0;
    this->emittance = 0;
    this->transmission = 0.0;
    this->ior = 1.0;
    this->color = Color();
}

Material::Material(double reflectivity, double diffuse, double emittance, double transmission, double ior, Color color)
{
    this->reflectivity = reflectivity;
    this->diffuse = diffuse;
    this->emittance = emittance;
    this->transmission = transmission;
    this->ior = ior;
    this->color = color;
}