#pragma once
#include "SpatialHash.h"
#include <cstring>

inline void spatialHashClear(SpatialHash &sh)
{
    memset(sh.counts, 0, sizeof(sh.counts));
}
