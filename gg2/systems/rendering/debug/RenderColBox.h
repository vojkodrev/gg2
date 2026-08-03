#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "RenderColCenter.h"
#include "../../../utils/collision/EntityColCenter.h"

static void renderColBox(
    const Context &ctx,
    SDL_FRect col,
    bool renderCenter = true)
{
    SDL_Renderer *renderer = ctx.renderer;
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;

    SDL_FPoint center;
    if (renderCenter)
        center = entityColCenter(col);
    col.x += off.x;
    col.y += off.y;
    if (!SDL_HasRectIntersectionFloat(&col, &screen))
        return;
    SDL_RenderRect(renderer, &col);
    if (renderCenter)
        renderColCenter(ctx, center);
}
