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

    if (ray->direction.dot(normal) > 0.0)
    {
        normal = normal * -1.0;
    }

    Vector3 reflectDirection = (ray->direction - normal * ray->direction.dot(normal) * 2.0).normalize();
    Vector3 randomDirection = Vector3(randomDouble() - 0.5, randomDouble() - 0.5, randomDouble() - 0.5).normalize();
    Vector3 rayDirection = reflectDirection.interpolate(randomDirection, material.diffuse).normalize();

    if (normal.dot(rayDirection) < 0)
    {
        rayDirection = rayDirection * -1.0;
    }

    Ray reflectRay = Ray(intersect.collisionPoint + rayDirection * 0.01, rayDirection);

    Color reflectColor = traceRay(&reflectRay, scene, camera, depth);

    Color refractColor;

    if (material.transmission > 0.0)
    {
        Vector3 refractDirection;

        if (ray->refract(normal, material.ior, &refractDirection))
        {
            Ray refractRay = Ray(intersect.collisionPoint + refractDirection * 0.01, refractDirection);

            refractColor = traceRay(&refractRay, scene, camera, depth);
        }
    }

    return material.color * material.emittance + reflectColor * material.reflectivity + material.color * reflectColor * (1 - material.reflectivity) + refractColor * material.transmission;
}