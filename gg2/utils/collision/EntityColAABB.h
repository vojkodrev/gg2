#pragma once
#include <SDL3/SDL.h>
#include "../../structs/entity/EntityBase.h"

template<int NEntities>
inline SDL_FRect entityColAABB(
    const EntityBase<NEntities> &base,
    uint32_t entityIndex,
    int collisionIndex,
    float buffer = 0.0f)
{
    if (base.animation.frameCount[entityIndex] == 0)
        return {0, 0, 0, 0};

    const int frameIndex = base.animation.frameIndex[entityIndex];
    if (!base.animation.frame.collision
            .exists[entityIndex][frameIndex][collisionIndex])
        return {0, 0, 0, 0};

    return {
        base.position.x[entityIndex] +
            base.animation.frame.collision.offX[entityIndex][frameIndex][collisionIndex] - buffer,
        base.position.y[entityIndex] +
            base.animation.frame.collision.offY[entityIndex][frameIndex][collisionIndex] - buffer,
        base.animation.frame.collision.w[entityIndex][frameIndex][collisionIndex] + buffer * 2,
        base.animation.frame.collision.h[entityIndex][frameIndex][collisionIndex] + buffer * 2
    };
}
