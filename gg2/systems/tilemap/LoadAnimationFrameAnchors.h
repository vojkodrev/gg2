#pragma once
#include "LoadAnchors.h"
#include "../../structs/animation/Animation.h"
#include <cstdint>

template<int NEntities>
inline void loadAnimationFrameAnchors(
    Animation<NEntities> &animation,
    uint32_t entityIndex,
    int frameIndex,
    const tmx::Tileset &tileset,
    uint32_t tileIndex,
    float scale)
{
    loadAnchors(
        animation.frame.anchor,
        entityIndex,
        frameIndex,
        tileset,
        tileIndex,
        "anchor",
        scale);
    loadAnchors(
        animation.frame.collision,
        entityIndex,
        frameIndex,
        tileset,
        tileIndex,
        "collision",
        scale);
}
