#pragma once
#include "../entity/EntityBase.h"

template<int N>
struct Ammo
{
    int zIndex[N] = {};
    EntityBase<N> base;
    bool exists[N] = {};
};
