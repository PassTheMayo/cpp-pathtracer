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
    int samples;

    Renderer(int width, int height, int samples);
    Color traceRay(Ray ray, Scene *scene, Camera camera, int depth);
};