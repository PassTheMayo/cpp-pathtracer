#pragma once

#include "triangle.h"
#include "scene.h"
#include "vector.h"

const double EPSILON = 0.0000000001;

double randomDouble();
Vector3 randomDirection();
void loadObjectFile(std::string filename, Scene *scene, Material material, Vector3 translate, Vector3 scale);