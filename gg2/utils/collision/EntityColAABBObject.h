#pragma once
#include <SDL3/SDL.h>
#include "Object.h"

inline SDL_FRect entityColAABB(const Object &object, uint32_t i, float buffer = 0.0f)
{
    int f = object.base.animation.frameIndex[i];
    return {
        object.base.position.x[i] + object.base.animation.frame.collision.offX[i][f] - buffer,
        object.base.position.y[i] + object.base.animation.frame.collision.offY[i][f] - buffer,
        object.base.animation.frame.collision.w[i][f] + buffer * 2,
        object.base.animation.frame.collision.h[i][f] + buffer * 2};
}
