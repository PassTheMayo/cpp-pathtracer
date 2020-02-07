#pragma once

#include <vector>
#include <memory>
#include "object.h"
#include "intersection.h"

class Scene
{
public:
    std::vector<std::unique_ptr<Object>> objects;

    Scene();
    Scene(const Scene &) = delete;
    void addObject(std::unique_ptr<Object> object);
    Intersection castRay(Ray *ray);
};