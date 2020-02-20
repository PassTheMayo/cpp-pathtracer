#pragma once

#include <vector>
#include <memory>
#include "object.h"
#include "skybox.h"
#include "intersection.h"

class Scene
{
public:
    Skybox *skybox = nullptr;
    std::vector<std::unique_ptr<Object>> objects;

    Scene();
    void setSkybox(Skybox *skybox);
    void addObject(std::unique_ptr<Object> object);
    Intersection castRay(Ray ray);
};