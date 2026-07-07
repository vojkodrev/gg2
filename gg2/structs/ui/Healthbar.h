#pragma once
#include "../core/EntityBase.h"

template<int N>
struct Healthbar
{
    EntityBase<N> base;
    bool show[N] = {};
    bool dirty[N] = {};
};
