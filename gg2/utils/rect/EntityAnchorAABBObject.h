#pragma once
#include <SDL3/SDL.h>
#include "Object.h"

inline SDL_FRect entityAnchorAABB(const Object &object, uint32_t i, float buffer = 0.0f)
{
    int f = object.base.animation.frameIndex[i];
    return {
        object.base.position.x[i] + object.base.animation.frame.anchor.offX[i][f] - buffer,
        object.base.position.y[i] + object.base.animation.frame.anchor.offY[i][f] - buffer,
        object.base.animation.frame.anchor.w[i][f] + buffer * 2,
        object.base.animation.frame.anchor.h[i][f] + buffer * 2
    };
}
