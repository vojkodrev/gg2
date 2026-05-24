#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "../../../utils/collision/EntityColCenter.h"

static void renderColBox(const Context &ctx, SDL_FRect col)
{
    SDL_Renderer *renderer = ctx.renderer;
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;

    col.x += off.x;
    col.y += off.y;
    if (!SDL_HasRectIntersectionFloat(&col, &screen))
        return;
    SDL_FPoint center = entityColCenter(col);
    SDL_RenderRect(renderer, &col);
    SDL_FRect pt = {center.x - 1, center.y - 1, 2, 2};
    SDL_RenderFillRect(renderer, &pt);
}
