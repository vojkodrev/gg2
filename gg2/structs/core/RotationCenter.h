#pragma once
#include "AnchorPoint.h"

template<int N>
struct RotationCenter
{
    AnchorPoint<N, 1> point;
    bool hasCenter[N];
};
