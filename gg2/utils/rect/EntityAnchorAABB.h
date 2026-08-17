#pragma once
#include <SDL3/SDL.h>
#include "../../structs/entity/EntityBase.h"

template<int NEntities>
inline SDL_FRect entityAnchorAABB(
    const EntityBase<NEntities> &base,
    uint32_t entityIndex,
    float buffer = 0.0f)
{
    if (base.animation.frameCount[entityIndex] == 0)
        return {0, 0, 0, 0};

    const int frameIndex = base.animation.frameIndex[entityIndex];
    return {
        base.position.x[entityIndex] +
            base.animation.frame.anchor.offX[entityIndex][frameIndex][0] - buffer,
        base.position.y[entityIndex] +
            base.animation.frame.anchor.offY[entityIndex][frameIndex][0] - buffer,
        base.animation.frame.anchor.w[entityIndex][frameIndex][0] + buffer * 2,
        base.animation.frame.anchor.h[entityIndex][frameIndex][0] + buffer * 2
    };
}
