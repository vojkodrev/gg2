#pragma once
#include "RotationCenter.h"

template<int N>
struct Rotation
{
    float initialAngle[N];
    float rotate[N];
    float initialRotate[N];
    RotationCenter<N> center;
};
