#pragma once
#include <SDL3/SDL.h>
#include "Context.h"

inline void renderColCenter(const Context &ctx, SDL_FPoint center, float size = 2.0f)
{
    const SDL_FPoint cameraOffset = ctx.data.camera.offset;
    const float halfSize = size / 2.0f;
    const SDL_FRect marker = {
        center.x + cameraOffset.x - halfSize,
        center.y + cameraOffset.y - halfSize,
        size,
        size
    };

    if (SDL_HasRectIntersectionFloat(&marker, &ctx.data.camera.screen))
        SDL_RenderFillRect(ctx.renderer, &marker);
}
