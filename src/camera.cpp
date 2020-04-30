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
    return Ray(position, (Vector3((x * 2.0 - 1.0) * (fov / 180), (y * 2.0 - 1.0) * (fov / 180) * aspectRatio, 1).normalize() * rotation.rollMat * rotation.pitchMat * rotation.yawMat).normalize());
}