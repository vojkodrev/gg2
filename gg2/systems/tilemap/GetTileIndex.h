#pragma once
#include "../../structs/tilemap/TileMapProperties.h"
#include <cstdint>

inline uint32_t getTileIndex(
    uint32_t gid,
    const TileMapProperties &props)
{
    return gid - props.firstGid;
}
