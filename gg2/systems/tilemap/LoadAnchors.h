#pragma once
#include "GetAnchors.h"
#include "../../structs/anchors/Anchor.h"
#include <cstdint>

template<int NEntities, int NFrames, int NAnchors>
inline void loadAnchors(
    Anchor<NEntities, NFrames, NAnchors> &anchors,
    uint32_t entityIndex,
    int frameIndex,
    const tmx::Tileset &tileset,
    uint32_t tileIndex,
    const char *name,
    float scale)
{
    SDL_FRect loadedAnchors[NAnchors] = {};
    const uint32_t anchorCount = getAnchors(
        tileset,
        tileIndex,
        name,
        loadedAnchors,
        NAnchors);

    for (int anchorIndex = 0; anchorIndex < NAnchors; anchorIndex++)
    {
        const SDL_FRect &anchor = loadedAnchors[anchorIndex];
        anchors.exists[entityIndex][frameIndex][anchorIndex] =
            anchorIndex < static_cast<int>(anchorCount);
        anchors.initialOffX[entityIndex][frameIndex][anchorIndex] = anchor.x;
        anchors.initialOffY[entityIndex][frameIndex][anchorIndex] = anchor.y;
        anchors.initialW[entityIndex][frameIndex][anchorIndex] = anchor.w;
        anchors.initialH[entityIndex][frameIndex][anchorIndex] = anchor.h;
        anchors.offX[entityIndex][frameIndex][anchorIndex] = anchor.x;
        anchors.offY[entityIndex][frameIndex][anchorIndex] = anchor.y;
        anchors.w[entityIndex][frameIndex][anchorIndex] = anchor.w * scale;
        anchors.h[entityIndex][frameIndex][anchorIndex] = anchor.h * scale;
    }
}
