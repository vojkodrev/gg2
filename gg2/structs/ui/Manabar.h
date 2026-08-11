#pragma once
#include "../entity/EntityBase.h"

template<int N>
struct Manabar
{
    EntityBase<N> base;
    bool show[N] = {};
    bool dirty[N] = {};
};
