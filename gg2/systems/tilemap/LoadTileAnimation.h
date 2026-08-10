#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <tmxlite/Tileset.hpp>
#include "../../structs/core/Animation.h"
#include "../../structs/core/AnimationStop.h"
#include "AnimationConstants.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "GetAnchor.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"

template<int N>
void loadTileAnimation(
    Animation<N> &animation,
    uint32_t n,
    const tmx::Tileset &tileset,
    uint32_t idx,
    const TileMapProperties &props,
    float scale)
{
    const tmx::Tileset::Tile *tileData = nullptr;
    for (auto &t : tileset.getTiles())
        if (t.ID == idx) { tileData = &t; break; }

    SDL_FRect col;
    const bool collisionFound =
        getAnchor(tileset, idx, "collision", col);
    SDL_FRect anchor;
    const bool anchorFound =
        getAnchor(tileset, idx, "anchor", anchor);
    float animationTime = getTileFloatProp(tileset, idx, "animationTime", 0.0f);
    animation.rotate[n] = 0.0f;
    animation.rotationStartAngle[n] = getTileFloatProp(tileset, idx, "animationStartAngle", 0.0f);
    animation.rotationStopAngle[n] = getTileFloatProp(tileset, idx, "animationStopAngle", 0.0f);
    animation.animationState[n] = AnimationState::Idle;
    animation.animationStop[n] = getTileStringProp(tileset, idx, "animationStop") == "afterFirstCycle"
        ? AnimationStop::AfterFirstCycle
        : AnimationStop::None;

    if (tileData && !tileData->animation.frames.empty())
    {
        int frameCount = (int)tileData->animation.frames.size();
        if (frameCount > MAX_ANIMATION_FRAMES) frameCount = MAX_ANIMATION_FRAMES;
        animation.animationType[n] = AnimationType::Sprite;
        animation.frameCount[n] = frameCount;
        animation.cycleDuration[n] = 0;
        for (int f = 0; f < frameCount; f++)
        {
            uint32_t fid = tileData->animation.frames[f].tileID - props.firstGid;
            animation.frame.src.x[n][f] = fid % props.tilesetW * props.srcTileW;
            animation.frame.src.y[n][f] = fid / props.tilesetW * props.srcTileH;
            animation.frame.src.w[n][f] = props.srcTileW;
            animation.frame.src.h[n][f] = props.srcTileH;
            animation.frame.anchor.exists[n][f] = anchorFound;
            animation.frame.anchor.initialOffX[n][f] = anchor.x;
            animation.frame.anchor.initialOffY[n][f] = anchor.y;
            animation.frame.anchor.initialW[n][f] = anchor.w;
            animation.frame.anchor.initialH[n][f] = anchor.h;
            animation.frame.anchor.offX[n][f] = anchor.x;
            animation.frame.anchor.offY[n][f] = anchor.y;
            animation.frame.anchor.w[n][f] = anchor.w * scale;
            animation.frame.anchor.h[n][f] = anchor.h * scale;
            animation.frame.collision.exists[n][f] = collisionFound;
            animation.frame.collision.initialOffX[n][f] = col.x;
            animation.frame.collision.initialOffY[n][f] = col.y;
            animation.frame.collision.initialW[n][f] = col.w;
            animation.frame.collision.initialH[n][f] = col.h;
            animation.frame.collision.offX[n][f] = col.x;
            animation.frame.collision.offY[n][f] = col.y;
            animation.frame.collision.w[n][f] = col.w * scale;
            animation.frame.collision.h[n][f] = col.h * scale;
            animation.frame.frameDuration[n][f] = tileData->animation.frames[f].duration;
            animation.cycleDuration[n] += animation.frame.frameDuration[n][f];
        }
        if (animationTime > 0.0f)
            animation.cycleDuration[n] = (uint64_t)animationTime;
    }
    else
    {
        animation.animationType[n] = getTileStringProp(tileset, idx, "animationType") == "rotation"
            ? AnimationType::Rotation
            : AnimationType::None;
        animation.frameCount[n] = 1;
        animation.cycleDuration[n] = animationTime > 0.0f ? (uint64_t)animationTime : 0;
        animation.frame.src.x[n][0] = idx % props.tilesetW * props.srcTileW;
        animation.frame.src.y[n][0] = idx / props.tilesetW * props.srcTileH;
        animation.frame.src.w[n][0] = props.srcTileW;
        animation.frame.src.h[n][0] = props.srcTileH;
        animation.frame.anchor.exists[n][0] = anchorFound;
        animation.frame.anchor.initialOffX[n][0] = anchor.x;
        animation.frame.anchor.initialOffY[n][0] = anchor.y;
        animation.frame.anchor.initialW[n][0] = anchor.w;
        animation.frame.anchor.initialH[n][0] = anchor.h;
        animation.frame.anchor.offX[n][0] = anchor.x;
        animation.frame.anchor.offY[n][0] = anchor.y;
        animation.frame.anchor.w[n][0] = anchor.w * scale;
        animation.frame.anchor.h[n][0] = anchor.h * scale;
        animation.frame.collision.exists[n][0] = collisionFound;
        animation.frame.collision.initialOffX[n][0] = col.x;
        animation.frame.collision.initialOffY[n][0] = col.y;
        animation.frame.collision.initialW[n][0] = col.w;
        animation.frame.collision.initialH[n][0] = col.h;
        animation.frame.collision.offX[n][0] = col.x;
        animation.frame.collision.offY[n][0] = col.y;
        animation.frame.collision.w[n][0] = col.w * scale;
        animation.frame.collision.h[n][0] = col.h * scale;
        animation.frame.frameDuration[n][0] = 0;
    }

    animation.frameIndex[n] = 0;
    animation.animationStartTime[n] = SDL_GetTicks();
}
