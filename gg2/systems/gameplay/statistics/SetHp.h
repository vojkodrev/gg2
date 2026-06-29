#pragma once
#include "../../../structs/core/Statistics.h"
#include <cstdint>

template<int N>
inline void setHp(
    Statistics<N> &statistics,
    uint32_t i,
    int hp)
{
    statistics.prevHp[i] = statistics.hp[i];
    statistics.hp[i] = hp;
    statistics.hpDirty[i] = statistics.prevHp[i] != statistics.hp[i];
}
