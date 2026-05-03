#pragma once
#include <SDL3/SDL.h>
#include "Context.h"

inline SDL_FPoint getCameraOffset(const Context &ctx)
{
    return {ctx.data.camera.position.w[0] * 0.5f - ctx.data.camera.position.x[0],
            ctx.data.camera.position.h[0] * 0.5f - ctx.data.camera.position.y[0]};
}
