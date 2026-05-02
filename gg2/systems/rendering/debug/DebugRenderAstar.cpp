#include "DebugRenderAstar.h"
#include "../../../structs/gameplay/ai/AStarPool.h"
#include "../../../structs/gameplay/ai/AStarStatus.h"

void debugRenderAstar(SDL_Renderer *renderer, const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 80);
    for (int i = 0; i < ctx.astarPool.count; i++)
    {
        const AStarContext &a = ctx.astarPool.ctx[i];
        SDL_FRect rect = { (float)a.searchX + off.x, (float)a.searchY + off.y, (float)a.searchW, (float)a.searchH };
        if (SDL_HasRectIntersectionFloat(&rect, &screen))
            SDL_RenderRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
