#pragma once
#include "../../structs/anchors/CenteredAnchor.h"
#include "../../structs/entity/EntityBase.h"
#include <cstdint>

template<int N>
inline void loadRangedCollision(
    CenteredAnchor<N, MAX_ANIMATION_FRAMES> &rangedCollision,
    const EntityBase<N> &npcBase,
    uint32_t entityIndex,
    int frameCount)
{
    const auto &entityCollisionAnchor = npcBase.animation.frame.collision;

    for (int frameIndex = 0; frameIndex < MAX_ANIMATION_FRAMES; frameIndex++)
        rangedCollision.anchor.exists[entityIndex][frameIndex] = false;

    for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
        rangedCollision.anchor.exists[entityIndex][frameIndex] =
            entityCollisionAnchor.exists[entityIndex][frameIndex];
}
