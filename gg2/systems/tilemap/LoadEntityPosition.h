#pragma once
#include "../../structs/core/EntityPosition.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "DecodeGridIndex.h"
#include <cstdint>

template<int N>
inline void loadEntityPosition(EntityPosition<N> &position, uint32_t entityIdx, uint32_t tileArrayIdx, const TileMapProperties &props)
{
    SDL_Point grid = decodeGridIndex((int)tileArrayIdx, props.mapW);
    position.x[entityIdx] = grid.x * props.dstTileW;
    position.y[entityIdx] = grid.y * props.dstTileH;
}
