#pragma once
#include "SetHp.h"
#include <algorithm>
#include <cstdint>

template<int N>
inline int setHpDamage(
    Statistics<N> &statistics,
    uint32_t i,
    int damage)
{
    const int hp = statistics.hp[i];
    const int nextHp = std::max(0, hp - damage);
    setHp(statistics, i, nextHp);
    return hp - nextHp;
}
