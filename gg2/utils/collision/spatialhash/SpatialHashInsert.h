#pragma once
#include <SDL3/SDL.h>
#include "SpatialHash.h"
#include "../../../structs/core/constants/SpatialHashConstants.h"
#include "SpatialHashInsertCell.h"

template<uint32_t N>
inline void spatialHashInsert(SpatialHash<N> &sh, uint32_t index, SDL_FRect rect, uint32_t id)
{
    int minCx = (int)(rect.x / SPATIAL_HASH_CELL_SIZE);
    int minCy = (int)(rect.y / SPATIAL_HASH_CELL_SIZE);
    int maxCx = (int)((rect.x + rect.w) / SPATIAL_HASH_CELL_SIZE);
    int maxCy = (int)((rect.y + rect.h) / SPATIAL_HASH_CELL_SIZE);
    for (int cy = minCy; cy <= maxCy; cy++)
        for (int cx = minCx; cx <= maxCx; cx++)
            spatialHashInsertCell(sh, index, cx, cy, id);
}
