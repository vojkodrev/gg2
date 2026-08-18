#pragma once
#include "../../../structs/entity/EntityBase.h"
#include "MirrorAnchorOffsetX.h"
#include <cstdint>

template<int N>
inline void mirrorEntityAnchorsAndCollisionOffsets(
    EntityBase<N> &entityBase,
    uint32_t entityIndex)
{
    if (!entityBase.facing.flipX[entityIndex])
        return;

    for (int frameIndex = 0;
        frameIndex < entityBase.animation.frameCount[entityIndex];
        frameIndex++)
    {
        mirrorAnchorOffsetX(
            entityBase.animation.frame.anchor,
            entityBase.position.w[entityIndex],
            entityIndex,
            frameIndex,
            0);
        for (int collisionIndex = 0;
            collisionIndex < MAX_FRAME_COLLISIONS;
            collisionIndex++)
            if (entityBase.animation.frame.collision
                    .exists[entityIndex][frameIndex][collisionIndex])
                mirrorAnchorOffsetX(
                    entityBase.animation.frame.collision,
                    entityBase.position.w[entityIndex],
                    entityIndex,
                    frameIndex,
                    collisionIndex);
    }
}
