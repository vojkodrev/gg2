#pragma once
#include "FacingDirection.h"

template<int N>
struct Facing
{
    FacingDirection facing[N];
    FacingDirection initialFacing[N];
    bool flipX[N];
};
