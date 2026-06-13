#pragma once
#include <SDL3/SDL.h>
#include "SpatialHash.h"
#include "SpatialHashInsertCell.h"

inline void spatialHashInsert(SpatialHash &sh, SDL_FRect rect, uint32_t id)
{
    int minCx = (int)(rect.x / SpatialHash::CELL_SIZE);
    int minCy = (int)(rect.y / SpatialHash::CELL_SIZE);
    int maxCx = (int)((rect.x + rect.w) / SpatialHash::CELL_SIZE);
    int maxCy = (int)((rect.y + rect.h) / SpatialHash::CELL_SIZE);
    for (int cy = minCy; cy <= maxCy; cy++)
        for (int cx = minCx; cx <= maxCx; cx++)
            spatialHashInsertCell(sh, cx, cy, id);
}
