#pragma once
#include "Context.h"

inline void renderDebugLine(
    const Context &ctx,
    float x1,
    float y1,
    float x2,
    float y2)
{
    if (!SDL_GetRectAndLineIntersectionFloat(
        &ctx.data.camera.screen,
        &x1,
        &y1,
        &x2,
        &y2))
        return;

    SDL_RenderLine(ctx.renderer, x1, y1, x2, y2);
}
