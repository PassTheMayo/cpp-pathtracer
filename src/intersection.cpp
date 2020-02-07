#include "intersection.h"

Intersection::Intersection(bool hit, double distance, Vector3 collisionPoint, Object *object)
{
    this->hit = hit;
    this->distance = distance;
    this->collisionPoint = collisionPoint;
    this->object = object;
}