#pragma once
#include "SpatialHash.h"
#include <cstring>

template<uint32_t N>
inline void spatialHashClear(SpatialHash<N> &sh, uint32_t index)
{
    memset(sh.counts[index], 0, sizeof(sh.counts[index]));
}
