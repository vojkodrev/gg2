#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <tmxlite/Tileset.hpp>
#include "../../structs/animation/Animation.h"
#include "../../structs/animation/AnimationStop.h"
#include "AnimationConstants.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "LoadAnimationFrameAnchors.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"

template<int N>
void loadTileAnimation(
    Animation<N> &animation,
    uint32_t entityIndex,
    const tmx::Tileset &tileset,
    uint32_t tileIndex,
    const TileMapProperties &props,
    float scale)
{
    const tmx::Tileset::Tile *tileData = nullptr;
    for (auto &t : tileset.getTiles())
        if (t.ID == tileIndex) { tileData = &t; break; }

    float animationTime =
        getTileFloatProp(tileset, tileIndex, "animationTime", 0.0f);
    animation.rotate[entityIndex] = 0.0f;
    animation.rotationStartAngle[entityIndex] =
        getTileFloatProp(tileset, tileIndex, "animationStartAngle", 0.0f);
    animation.rotationStopAngle[entityIndex] =
        getTileFloatProp(tileset, tileIndex, "animationStopAngle", 0.0f);
    animation.animationState[entityIndex] = AnimationState::Idle;
    animation.animationStop[entityIndex] =
        getTileStringProp(tileset, tileIndex, "animationStop") ==
            "afterFirstCycle"
        ? AnimationStop::AfterFirstCycle
        : AnimationStop::None;

    if (tileData && !tileData->animation.frames.empty())
    {
        int frameCount = (int)tileData->animation.frames.size();
        if (frameCount > MAX_ANIMATION_FRAMES) frameCount = MAX_ANIMATION_FRAMES;
        animation.animationType[entityIndex] = AnimationType::Sprite;
        animation.frameCount[entityIndex] = frameCount;
        animation.cycleDuration[entityIndex] = 0;
        for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
        {
            uint32_t frameTileIndex =
                tileData->animation.frames[frameIndex].tileID - props.firstGid;
            animation.frame.src.x[entityIndex][frameIndex] =
                frameTileIndex % props.tilesetW * props.srcTileW;
            animation.frame.src.y[entityIndex][frameIndex] =
                frameTileIndex / props.tilesetW * props.srcTileH;
            animation.frame.src.w[entityIndex][frameIndex] = props.srcTileW;
            animation.frame.src.h[entityIndex][frameIndex] = props.srcTileH;
            loadAnimationFrameAnchors(
                animation,
                entityIndex,
                frameIndex,
                tileset,
                frameTileIndex,
                scale);
            animation.frame.frameDuration[entityIndex][frameIndex] =
                tileData->animation.frames[frameIndex].duration;
            animation.cycleDuration[entityIndex] +=
                animation.frame.frameDuration[entityIndex][frameIndex];
        }
        if (animationTime > 0.0f)
            animation.cycleDuration[entityIndex] = (uint64_t)animationTime;
    }
    else
    {
        animation.animationType[entityIndex] =
            getTileStringProp(tileset, tileIndex, "animationType") ==
                "rotation"
            ? AnimationType::Rotation
            : AnimationType::None;
        animation.frameCount[entityIndex] = 1;
        animation.cycleDuration[entityIndex] =
            animationTime > 0.0f ? (uint64_t)animationTime : 0;
        animation.frame.src.x[entityIndex][0] =
            tileIndex % props.tilesetW * props.srcTileW;
        animation.frame.src.y[entityIndex][0] =
            tileIndex / props.tilesetW * props.srcTileH;
        animation.frame.src.w[entityIndex][0] = props.srcTileW;
        animation.frame.src.h[entityIndex][0] = props.srcTileH;
        loadAnimationFrameAnchors(
            animation,
            entityIndex,
            0,
            tileset,
            tileIndex,
            scale);
        animation.frame.frameDuration[entityIndex][0] = 0;
    }

    animation.frameIndex[entityIndex] = 0;
    animation.animationStartTime[entityIndex] = SDL_GetTicks();
}
