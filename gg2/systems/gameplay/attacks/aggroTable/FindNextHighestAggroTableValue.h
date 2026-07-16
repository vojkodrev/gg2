#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include <cstdint>

template<int N>
float findNextHighestAggroTableValue(
    const AggroTable<N> &aggroTable,
    uint32_t n,
    int maxSlot)
{
    float nextHighestValue = 0.0f;
    for (uint32_t i = 0; i < aggroTable.pool.count[n]; i++)
    {
        if (!aggroTable.pool.active[n][i] || i == (uint32_t)maxSlot)
            continue;

        if (aggroTable.value[n][i] > nextHighestValue)
            nextHighestValue = aggroTable.value[n][i];
    }

    return nextHighestValue;
}
