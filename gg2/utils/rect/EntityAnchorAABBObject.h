#pragma once
#include <SDL3/SDL.h>
#include "Object.h"

inline SDL_FRect entityAnchorAABB(const Object &object, uint32_t i, float buffer = 0.0f)
{
    int f = object.animation.frameIndex[i];
    return {
        object.position.x[i] + object.animation.frame.anchor.offX[i][f] - buffer,
        object.position.y[i] + object.animation.frame.anchor.offY[i][f] - buffer,
        object.animation.frame.anchor.w[i][f] + buffer * 2,
        object.animation.frame.anchor.h[i][f] + buffer * 2
    };
}
