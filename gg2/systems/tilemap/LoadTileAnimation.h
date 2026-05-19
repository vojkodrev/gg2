#pragma once
#include <cstdint>
#include <tmxlite/Tileset.hpp>
#include "../../structs/core/Animation.h"
#include "CapacityConstants.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "GetCollision.h"

template<int N>
void loadTileAnimation(Animation<N> &animation, uint32_t n, const tmx::Tileset &tileset, uint32_t idx, const TileMapProperties &props)
{
    const tmx::Tileset::Tile *tileData = nullptr;
    for (auto &t : tileset.getTiles())
        if (t.ID == idx) { tileData = &t; break; }

    SDL_FRect col = getCollision(tileset, idx);

    if (tileData && !tileData->animation.frames.empty())
    {
        int frameCount = (int)tileData->animation.frames.size();
        if (frameCount > MAX_ANIMATION_FRAMES) frameCount = MAX_ANIMATION_FRAMES;
        animation.frameCount[n] = frameCount;
        for (int f = 0; f < frameCount; f++)
        {
            uint32_t fid = tileData->animation.frames[f].tileID - props.firstGid;
            animation.frame.src.x[n][f] = fid % props.columns * props.srcTileW;
            animation.frame.src.y[n][f] = fid / props.columns * props.srcTileH;
            animation.frame.src.w[n][f] = props.srcTileW;
            animation.frame.src.h[n][f] = props.srcTileH;
            animation.frame.src.rotate[n][f] = 0;
            animation.frame.collision.offX[n][f] = col.x;
            animation.frame.collision.offY[n][f] = col.y;
            animation.frame.collision.w[n][f] = col.w;
            animation.frame.collision.h[n][f] = col.h;
            animation.frame.frameDuration[n][f] = tileData->animation.frames[f].duration;
        }
    }
    else
    {
        animation.frameCount[n] = 1;
        animation.frame.src.x[n][0] = idx % props.columns * props.srcTileW;
        animation.frame.src.y[n][0] = idx / props.columns * props.srcTileH;
        animation.frame.src.w[n][0] = props.srcTileW;
        animation.frame.src.h[n][0] = props.srcTileH;
        animation.frame.src.rotate[n][0] = 0;
        animation.frame.collision.offX[n][0] = col.x;
        animation.frame.collision.offY[n][0] = col.y;
        animation.frame.collision.w[n][0] = col.w;
        animation.frame.collision.h[n][0] = col.h;
        animation.frame.frameDuration[n][0] = 0;
    }

    animation.frameIndex[n] = 0;
    animation.animationStartTime[n] = 0;
}
