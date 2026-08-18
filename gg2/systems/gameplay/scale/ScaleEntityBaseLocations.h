#pragma once
#include "../../../structs/entity/EntityBase.h"
#include "ScaleAnchorLocation.h"
#include <cstdint>

template<int N>
inline void scaleEntityBaseLocations(
    EntityBase<N> &entityBase,
    uint32_t entityIndex)
{
    for (int frameIndex = 0;
        frameIndex < entityBase.animation.frameCount[entityIndex];
        frameIndex++)
    {
        scaleAnchorLocation(
            entityBase.animation.frame.anchor,
            entityBase.scale.value[entityIndex],
            entityIndex,
            frameIndex,
            0);
        for (int collisionIndex = 0;
            collisionIndex < MAX_FRAME_COLLISIONS;
            collisionIndex++)
            if (entityBase.animation.frame.collision
                    .exists[entityIndex][frameIndex][collisionIndex])
                scaleAnchorLocation(
                    entityBase.animation.frame.collision,
                    entityBase.scale.value[entityIndex],
                    entityIndex,
                    frameIndex,
                    collisionIndex);
    }
}
