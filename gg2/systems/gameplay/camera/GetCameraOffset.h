#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "Constants.h"

inline SDL_FPoint getCameraOffset(const Context &ctx)
{
    return {SCREEN_W * 0.5f - ctx.data.camera.x, SCREEN_H * 0.5f - ctx.data.camera.y};
}
