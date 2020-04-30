#include <iostream>
#include "util.h"
#include "material.h"
#include "ray.h"
#include "renderer.h"
#include "util.h"

Renderer::Renderer(int width, int height, int samples, int mode, double lightFalloff)
{
    this->width = width;
    this->height = height;
    this->samples = samples;
    this->mode = mode;
    this->lightFalloff = lightFalloff;
}

Color Renderer::traceRay(Ray ray, Scene *scene, Camera camera, int depth)
{
    if (depth >= camera.maxBounces)
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

    if (mode == 2)
    {
        return Color(255.0, 255.0, 255.0) * (1.0 / camera.position.distance(intersect.collisionPoint));
    }

    Material material = intersect.object->getMaterial();

    if (material.emittance > 0.0)
    {
        return material.color * material.emittance;
    }

    Vector3 normal = intersect.object->calculateNormal(intersect.collisionPoint);

    if (normal.dot(ray.direction) > 0.0)
    {
        normal = normal * -1.0;
    }

    if (mode == 1)
    {
        return normal;
    }

    Color refractColor;
    Color bounceColor;
    Color specularColor;

    if (material.transmission > 0.0)
    {
        Vector3 refractDirection;

        if (ray.refract(normal, material.ior, &refractDirection))
        {
            refractColor = traceRay(Ray(intersect.collisionPoint + refractDirection * EPSILON, refractDirection), scene, camera, depth + 1);
        }
    }

    if (material.transmission < 1 || material.specularity > 0.0)
    {
        Vector3 diffuseDirection = randomDirection();

        if (normal.dot(diffuseDirection) < 0.0)
        {
            diffuseDirection = diffuseDirection * -1.0;
        }

        Vector3 bounceDirection = ray.reflect(normal).interpolate(diffuseDirection, material.roughness);

        if (material.transmission < 1.0)
        {
            bounceColor = traceRay(Ray(intersect.collisionPoint + bounceDirection * EPSILON, bounceDirection), scene, camera, depth + 1);
        }

        if (material.specularity > 0.0)
        {
            Intersection specularHit = scene->castRay(Ray(intersect.collisionPoint + bounceDirection * EPSILON, bounceDirection));

            if (specularHit.hit)
            {
                specularColor = Color(specularHit.object->getMaterial().emittance);
            }
        }
    }

    Color objectColor = material.color;

    if (material.texture)
    {
        Vector3 uv = intersect.object->calculateUVCoordinates(intersect.collisionPoint, normal);

        objectColor = material.texture->getColorAt(uv);
    }

    double falloff = 1.0;

    if (depth != 0)
    {
        falloff = 1.0 - lightFalloff;
    }

    return (objectColor * bounceColor.interpolate(refractColor, material.transmission) + specularColor) * falloff;
}