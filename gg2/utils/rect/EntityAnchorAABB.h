#pragma once
#include <SDL3/SDL.h>
#include "../../structs/core/EntityBase.h"

template<int N>
inline SDL_FRect entityAnchorAABB(const EntityBase<N> &base, uint32_t i, float buffer = 0.0f)
{
    if (base.animation.frameCount[i] == 0)
        return {0, 0, 0, 0};

    int f = base.animation.frameIndex[i];
    return {
        base.position.x[i] + base.animation.frame.anchor.offX[i][f] - buffer,
        base.position.y[i] + base.animation.frame.anchor.offY[i][f] - buffer,
        base.animation.frame.anchor.w[i][f] + buffer * 2,
        base.animation.frame.anchor.h[i][f] + buffer * 2
    };
}
