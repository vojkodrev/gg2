#include "DebugRenderPlayer.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABBPlayer.h"

void debugRenderPlayer(SDL_Renderer *renderer, const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    renderColBox(renderer, entityColAABB(ctx.data.player), off, screen);
}
