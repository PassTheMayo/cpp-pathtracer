#pragma once

#include "triangle.h"
#include "scene.h"
#include "vector.h"

const double EPSILON = 0.0000000001;

double randomDouble();
Vector3 randomDirection();
void loadObjectFile(std::string filename, Scene *scene, Material material, Vector3 translate, Vector3 scale);
double interpolate(double a, double b, double s);
void createCube(Scene *scene, Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, Vector3 h, Material material);