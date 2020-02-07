#pragma once

#include <array>

class Rotation
{
public:
    double pitch;
    double yaw;
    double roll;
    std::array<std::array<double, 3>, 3> pitchMat;
    std::array<std::array<double, 3>, 3> yawMat;
    std::array<std::array<double, 3>, 3> rollMat;

    Rotation();
    Rotation(double pitch, double yaw, double roll);
    void updatePitchMat();
    void updateYawMat();
    void updateRollMat();
};