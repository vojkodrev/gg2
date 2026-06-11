#pragma once
#include "RotationCenter.h"

template<int N>
struct Rotation
{
    float rotate[N];
    float initialRotate[N];
    float initialAngle[N];
    RotationCenter<N> center;
};
