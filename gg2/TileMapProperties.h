#pragma once
#include <cstdint>

struct TileMapProperties
{
    uint32_t srcTileW, srcTileH;
    uint32_t columns;
    uint32_t mapW;
    uint32_t dstTileW, dstTileH;
    uint32_t firstGid;
};
