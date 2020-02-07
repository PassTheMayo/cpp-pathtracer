#include <iostream>
#include "material.h"
#include "ray.h"
#include "renderer.h"

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

    if (material.emittance == 1)
    {
        return material.color;
    }

    Vector3 normal = intersect.object->calculateNormal(intersect.collisionPoint);

    double randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    double randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    double randomZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    Vector3 reflectDirection = ray->direction.subtract(normal.multiply(ray->direction.dot(normal) * 2)).normalize().interpolate(Vector3(randomX * 2 - 1, randomY * 2 - 1, randomZ * 2 - 1), material.diffuse).normalize();

    if (normal.dot(reflectDirection) < 0)
    {
        reflectDirection = reflectDirection * -1.0;
    }

    Ray reflectRay = Ray(intersect.collisionPoint + reflectDirection * 0.01, reflectDirection);

    Color reflectColor = traceRay(&reflectRay, scene, camera, depth);

    return material.color.interpolate(reflectColor, material.reflectivity);
}