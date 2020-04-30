#include "material.h"

Material::Material()
{
    this->metallic = 0.0;
    this->roughness = 0.0;
    this->specularity = 0.0;
    this->emittance = 0.0;
    this->transmission = 0.0;
    this->ior = 1.0;
    this->color = Color();
    this->texture = nullptr;
}

Material::Material(double metallic, double roughness, double specularity, double emittance, double transmission, double ior, Color color, Texture *texture)
{
    this->metallic = metallic;
    this->roughness = roughness;
    this->specularity = specularity;
    this->emittance = emittance;
    this->transmission = transmission;
    this->ior = ior;
    this->color = color;
    this->texture = texture;
}