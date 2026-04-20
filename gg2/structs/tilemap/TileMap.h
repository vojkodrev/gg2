#pragma once
#include <cstdint>
#include "Tile.h"

struct TileMap
{
    uint32_t tileCount;
    Tile tiles;
};
