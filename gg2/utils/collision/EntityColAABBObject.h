#pragma once
#include <SDL3/SDL.h>
#include "Object.h"

inline SDL_FRect entityColAABB(const Object &object, uint32_t i, float buffer = 0.0f)
{
    return {
        object.position.x[i] + object.collision.offX[i] - buffer,
        object.position.y[i] + object.collision.offY[i] - buffer,
        object.collision.w[i] + buffer * 2,
        object.collision.h[i] + buffer * 2};
}
