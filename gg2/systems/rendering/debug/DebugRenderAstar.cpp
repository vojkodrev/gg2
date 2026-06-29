#include "DebugRenderAstar.h"
#include "../../../structs/ai/AStarPool.h"
#include "../../../structs/ai/AStarStatus.h"

void debugRenderAstar(const Context &ctx)
{
    if (!ctx.data.debug.showNavigation)
        return;

    SDL_Renderer *renderer = ctx.renderer;
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int i = 0; i < MAX_ASTARS; i++)
    {
        const auto &a = ctx.astarPool.ctx;
        if (a.searchW[i] <= 0 || a.searchH[i] <= 0)
            continue;

        SDL_FRect rect = {
            (float)a.searchX[i] + off.x,
            (float)a.searchY[i] + off.y,
            (float)a.searchW[i],
            (float)a.searchH[i]
        };
        if (SDL_HasRectIntersectionFloat(&rect, &screen))
            SDL_RenderRect(renderer, &rect);
    }
}
