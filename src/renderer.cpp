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
    Vector3 diffuseDirection = randomDirection();

    if (normal.dot(diffuseDirection) < 0)
    {
        diffuseDirection = diffuseDirection * -1.0;
    }

    Color reflectColor = traceRay(Ray(intersect.collisionPoint + reflectDirection * EPSILON, reflectDirection), scene, camera, depth);
    Color diffuseColor = traceRay(Ray(intersect.collisionPoint + diffuseDirection * EPSILON, diffuseDirection), scene, camera, depth);
    Color bounceColor = reflectColor.interpolate(diffuseColor, material.diffuse);

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

    return materialColor * material.emittance + bounceColor * material.reflectivity + material.color * bounceColor * (1 - material.reflectivity) + refractColor * material.transmission;
}