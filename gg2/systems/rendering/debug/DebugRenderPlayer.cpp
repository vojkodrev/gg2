#include "DebugRenderPlayer.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityAnchorAABBPlayer.h"
#include "../../../utils/collision/EntityColAABBPlayer.h"

void debugRenderPlayer(const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_Renderer *renderer = ctx.renderer;
    const auto &player = ctx.data.player;

    SDL_FRect col = entityColAABB(player);
    if (col.w > 0.0f && col.h > 0.0f)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        renderColBox(renderer, col, off, screen);
    }

    SDL_FRect anchor = entityAnchorAABB(player);
    if (anchor.w <= 0.0f || anchor.h <= 0.0f)
        return;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    renderColBox(renderer, anchor, off, screen);
}
