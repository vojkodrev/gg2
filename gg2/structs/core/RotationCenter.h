#pragma once
#include "AnchorPoint.h"

template<int N>
struct RotationCenter
{
    AnchorPoint<N> point;
    bool hasCenter[N];
};
