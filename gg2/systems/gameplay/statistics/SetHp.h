#pragma once
#include "../../../structs/statistics/Statistics.h"
#include <cstdint>

template<int N>
inline void setHp(
    Statistics<N> &statistics,
    uint32_t i,
    int hp)
{
    statistics.health.prevHp[i] = statistics.health.hp[i];
    statistics.health.hp[i] = hp;
    statistics.health.dirty[i] =
        statistics.health.prevHp[i] != statistics.health.hp[i];
}
