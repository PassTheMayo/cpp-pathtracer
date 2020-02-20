#include <iostream>
#include "util.h"
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

Color Renderer::traceRay(Ray ray, Scene *scene, Camera *camera, int depth)
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
            return scene->skybox->getColor(ray.direction);
        }

        return Color(0.0, 0.0, 0.0);
    }

    Material material = intersect.object->getMaterial();
    Vector3 normal = intersect.object->calculateNormal(intersect.collisionPoint);

    if (ray.direction.dot(normal) > 0.0)
    {
        normal = normal * -1.0;
    }

    Vector3 reflectDirection = (ray.direction - normal * ray.direction.dot(normal) * 2.0).normalize();
    Vector3 randomDirection = Vector3(randomDouble() - 0.5, randomDouble() - 0.5, randomDouble() - 0.5).normalize();
    Vector3 rayDirection = reflectDirection.interpolate(randomDirection, material.diffuse).normalize();

    if (normal.dot(rayDirection) < 0)
    {
        rayDirection = rayDirection * -1.0;
    }

    Color reflectColor = traceRay(Ray(intersect.collisionPoint + rayDirection * EPSILON, rayDirection), scene, camera, depth);

    Color refractColor;

    if (material.transmission > 0.0)
    {
        Vector3 refractDirection;

        if (ray.refract(normal, material.ior, &refractDirection))
        {
            refractColor = traceRay(Ray(intersect.collisionPoint + refractDirection * 0.01, refractDirection), scene, camera, depth);
        }
    }

    Color materialColor = material.color;

    if (material.texture)
    {
        Vector3 uv = intersect.object->calculateUVCoordinates(intersect.collisionPoint, normal);

        materialColor = material.texture->getColorAt(uv);
    }

    return materialColor * material.emittance + reflectColor * material.reflectivity + material.color * reflectColor * (1 - material.reflectivity) + refractColor * material.transmission;
}