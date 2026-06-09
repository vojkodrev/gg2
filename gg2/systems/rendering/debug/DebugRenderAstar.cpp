#include "DebugRenderAstar.h"
#include "../../../structs/gameplay/ai/AStarPool.h"
#include "../../../structs/gameplay/ai/AStarStatus.h"

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
        const AStarContext &a = ctx.astarPool.ctx[i];
        if (a.searchW <= 0 || a.searchH <= 0)
            continue;

        SDL_FRect rect = { (float)a.searchX + off.x, (float)a.searchY + off.y, (float)a.searchW, (float)a.searchH };
        if (SDL_HasRectIntersectionFloat(&rect, &screen))
            SDL_RenderRect(renderer, &rect);
    }
}
