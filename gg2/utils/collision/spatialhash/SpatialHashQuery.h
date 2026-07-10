#pragma once
#include <SDL3/SDL.h>
#include "SpatialHash.h"
#include "../../../structs/core/constants/SpatialHashConstants.h"
#include "SpatialHashQueryCell.h"

template<uint32_t N>
inline int spatialHashQuery(
    const SpatialHash<N> &sh,
    uint32_t index,
    SDL_FRect rect,
    uint32_t *out,
    int maxOut)
{
    int minCx = (int)(rect.x / SPATIAL_HASH_CELL_SIZE);
    int minCy = (int)(rect.y / SPATIAL_HASH_CELL_SIZE);
    int maxCx = (int)((rect.x + rect.w) / SPATIAL_HASH_CELL_SIZE);
    int maxCy = (int)((rect.y + rect.h) / SPATIAL_HASH_CELL_SIZE);
    int total = 0;
    for (int cy = minCy; cy <= maxCy && total < maxOut; cy++)
        for (int cx = minCx; cx <= maxCx && total < maxOut; cx++)
            total += spatialHashQueryCell(sh, index, cx, cy, out + total, maxOut - total);
    return total;
}
