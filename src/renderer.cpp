#include <iostream>
#include "material.h"
#include "ray.h"
#include "renderer.h"
#include "util.h"

Renderer::Renderer(int width, int height, int samples)
{
    this->width = width;
    this->height = height;
    this->samples = samples;
}

Color Renderer::traceRay(Ray *ray, Scene *scene, Camera *camera, int depth)
{
    depth++;

    if (depth >= camera->maxBounces)
    {
        return Color(0.0, 0.0, 0.0);
    }

    Intersection intersect = scene->castRay(ray);

    if (!intersect.hit)
    {
        if (scene->skybox)
        {
            return scene->skybox->getColor(ray->direction);
        }

        return Color(0.0, 0.0, 0.0);
    }

    Material material = intersect.object->getMaterial();
    Vector3 normal = intersect.object->calculateNormal(intersect.collisionPoint);

    if (material.emittance == 1)
    {
        return material.color;
    }

    Vector3 reflectDirection = ray->direction.subtract(normal.multiply(ray->direction.dot(normal) * 2)).normalize().interpolate(Vector3(randomDouble() * 2 - 1, randomDouble() * 2 - 1, randomDouble() * 2 - 1), material.diffuse).normalize();

    if (normal.dot(reflectDirection) < 0)
    {
        reflectDirection = reflectDirection * -1.0;
    }

    Ray reflectRay = Ray(intersect.collisionPoint + reflectDirection * 0.01, reflectDirection);

    Color reflectColor = traceRay(&reflectRay, scene, camera, depth);

    return material.color.multiply(reflectColor.magnitude()).interpolate(reflectColor, material.reflectivity);
}