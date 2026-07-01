#pragma once
#include "../core/EntityBase.h"

template<int N>
struct Manabar
{
    EntityBase<N> base;
    bool show[N] = {};
};
