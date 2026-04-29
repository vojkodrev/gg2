#pragma once
#include <SDL3/SDL.h>
#include "SpatialHash.h"
#include "SpatialHashQueryCell.h"

inline int spatialHashQuery(const SpatialHash &sh, SDL_FRect rect, uint16_t *out, int maxOut)
{
    int minCx = (int)(rect.x / SpatialHash::CELL_SIZE);
    int minCy = (int)(rect.y / SpatialHash::CELL_SIZE);
    int maxCx = (int)((rect.x + rect.w) / SpatialHash::CELL_SIZE);
    int maxCy = (int)((rect.y + rect.h) / SpatialHash::CELL_SIZE);
    int total = 0;
    for (int cy = minCy; cy <= maxCy && total < maxOut; cy++)
        for (int cx = minCx; cx <= maxCx && total < maxOut; cx++)
            total += spatialHashQueryCell(sh, cx, cy, out + total, maxOut - total);
    return total;
}
