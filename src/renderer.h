#pragma once

#include "color.h"
#include "ray.h"
#include "scene.h"
#include "camera.h"

class Renderer
{
public:
    int width;
    int height;

    Renderer(int width, int height);
    Color traceRay(Ray ray, Scene scene, Camera camera);
};