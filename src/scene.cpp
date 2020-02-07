#include <iostream>
#include "scene.h"
#include "object.h"

Scene::Scene() {}

void Scene::addObject(Object *object)
{
    objects.emplace_back(object);
}

Intersection Scene::castRay(Ray ray)
{
    Object *object;
    double closestDistance = -1;

    for (int i = 0; i < objects.size(); i++)
    {
        double dist = objects[i]->calculateIntersection(ray);

        if (dist > -1)
        {
            printf("Hit sphere\n");
        }

        if (dist >= 0 && (dist < closestDistance || closestDistance < 0))
        {
            closestDistance = dist;
            object = objects[i];
        }
    }

    return Intersection(closestDistance >= 0, closestDistance, ray.across(closestDistance), object);
}