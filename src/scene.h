#pragma once

#include <vector>
#include <memory>
#include "object.h"
#include "intersection.h"

class Scene
{
public:
    std::vector<Object *> objects;

    Scene();
    void addObject(Object *object);
    Intersection castRay(Ray ray);
};