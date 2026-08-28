#pragma once
#include "../entity/EntityBase.h"

template<int N>
struct ProgressBar
{
    int zIndex[N] = {};
    EntityBase<N> base;
    bool show[N] = {};
    bool dirty[N] = {};
};
