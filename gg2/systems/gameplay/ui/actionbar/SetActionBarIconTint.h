#pragma once
#include "../../../../structs/core/Tint.h"

template<int N>
inline void setActionBarIconTint(
    Tint<N> &tint,
    int index,
    float r,
    float g,
    float b,
    float a)
{
    tint.r[index] = r;
    tint.g[index] = g;
    tint.b[index] = b;
    tint.a[index] = a;
}
