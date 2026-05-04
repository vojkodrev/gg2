#pragma once
#include <cstdint>
#include "CapacityConstants.h"

struct Tile
{
    uint32_t srcX[MAX_TILES];
    uint32_t srcY[MAX_TILES];
    int32_t dstX[MAX_TILES];
    int32_t dstY[MAX_TILES];
};
