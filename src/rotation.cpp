#include <iostream>
#include <math.h>
#include "rotation.h"

Rotation::Rotation() {}

Rotation::Rotation(double pitch, double yaw, double roll)
{
    this->pitch = pitch;
    this->yaw = yaw;
    this->roll = roll;

    updatePitchMat();
    updateYawMat();
    updateRollMat();
}

void Rotation::updatePitchMat()
{
    pitchMat = {{{1, 0, 0},
                 {0, cos(pitch), -sin(pitch)},
                 {0, sin(pitch), cos(pitch)}}};
}

void Rotation::updateYawMat()
{
    yawMat = {{{cos(yaw), 0, sin(yaw)},
               {0, 1, 0},
               {-sin(yaw), 0, cos(yaw)}}};
}

void Rotation::updateRollMat()
{
    rollMat = {{{cos(roll), -sin(roll), 0},
                {sin(roll), cos(roll), 0},
                {0, 0, 1}}};
}