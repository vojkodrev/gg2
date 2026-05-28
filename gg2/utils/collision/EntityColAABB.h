#pragma once
#include <SDL3/SDL.h>
#include "../../structs/core/EntityBase.h"

template<int N>
inline SDL_FRect entityColAABB(const EntityBase<N> &base, uint32_t i, float buffer = 0.0f)
{
    if (base.animation.frameCount[i] == 0)
        return {0, 0, 0, 0};

    int f = base.animation.frameIndex[i];
    return {
        base.position.x[i] + base.animation.frame.collision.offX[i][f] - buffer,
        base.position.y[i] + base.animation.frame.collision.offY[i][f] - buffer,
        base.animation.frame.collision.w[i][f] + buffer * 2,
        base.animation.frame.collision.h[i][f] + buffer * 2
    };
}
