#pragma once
#include "../entity/EntityBase.h"

template<int N>
struct Ammo
{
    EntityBase<N> base;
    bool exists[N] = {};
};
