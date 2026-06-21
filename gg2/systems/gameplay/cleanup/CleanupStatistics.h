#pragma once
#include "../../../structs/core/Statistics.h"
#include <cstdint>

template<int N>
inline void cleanupStatistics(Statistics<N> &statistics, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        statistics.hpDirty[i] = false;
}
