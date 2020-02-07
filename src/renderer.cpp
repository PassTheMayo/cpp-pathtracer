#include <iostream>
#include "material.h"
#include "renderer.h"

Renderer::Renderer(int width, int height)
{
    this->width = width;
    this->height = height;
}

Color Renderer::traceRay(Ray *ray, Scene *scene, Camera *camera)
{
    Intersection intersect = scene->castRay(ray);

    if (!intersect.hit)
    {
        return Color(0.0, 0.0, 0.0);
    }

    Material material = intersect.object->getMaterial();

    return material.color;
}