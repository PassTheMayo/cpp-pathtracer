#include <iostream>
#include "camera.h"

Camera::Camera(Vector3 position, Rotation rotation, double fov)
{
    this->position = position;
    this->rotation = rotation;
    this->fov = fov;
}

Ray Camera::getRay(double x, double y, double aspectRatio)
{
    Vector3 direction = Vector3(x - 0.5, (y - 0.5) * aspectRatio, 1).normalize();

    direction = direction.multiply(rotation.rollMat);
    direction = direction.multiply(rotation.pitchMat);
    direction = direction.multiply(rotation.yawMat);
    direction = direction.normalize();

    return Ray(position, direction);
}