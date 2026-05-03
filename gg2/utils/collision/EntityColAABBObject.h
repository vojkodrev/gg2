#pragma once
#include <SDL3/SDL.h>
#include "Object.h"

inline SDL_FRect entityColAABB(const Object &object, uint32_t i, float buffer = 0.0f)
{
    int f = object.animation.frameIndex[i];
    return {
        object.position.x[i] + object.animation.frame.collision.offX[i][f] - buffer,
        object.position.y[i] + object.animation.frame.collision.offY[i][f] - buffer,
        object.animation.frame.collision.w[i][f] + buffer * 2,
        object.animation.frame.collision.h[i][f] + buffer * 2};
}
