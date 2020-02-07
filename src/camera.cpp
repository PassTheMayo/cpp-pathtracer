#include "camera.h"

Camera::Camera(Vector3 position, Rotation rotation, double aspectRatio, double fov, int maxBounces)
{
    this->position = position;
    this->rotation = rotation;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->maxBounces = maxBounces;
}

Ray Camera::getRay(double x, double y)
{
    Vector3 direction = Vector3((x - 0.5) * (fov / 180), (y - 0.5) * (fov / 180) * aspectRatio, 1).normalize();

    direction = direction.multiply(rotation.rollMat);
    direction = direction.multiply(rotation.pitchMat);
    direction = direction.multiply(rotation.yawMat);
    direction = direction.normalize();

    return Ray(position, direction);
}