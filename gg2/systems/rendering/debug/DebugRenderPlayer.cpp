#include "DebugRenderPlayer.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABBPlayer.h"

void debugRenderPlayer(const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_Renderer *renderer = ctx.renderer;
    const auto &player = ctx.data.player;
    const int f = player.animation.frameIndex[0];

    SDL_FRect col = entityColAABB(player);
    if (col.w > 0.0f && col.h > 0.0f)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        renderColBox(renderer, col, off, screen);
    }

    SDL_FRect anchor = {
        player.animation.frame.anchor.offX[0][f],
        player.animation.frame.anchor.offY[0][f],
        player.animation.frame.anchor.w[0][f],
        player.animation.frame.anchor.h[0][f]
    };
    if (anchor.w <= 0.0f || anchor.h <= 0.0f)
        return;

    anchor.x = player.position.x[0] + anchor.x;
    anchor.y = player.position.y[0] + anchor.y;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    renderColBox(renderer, anchor, off, screen);
}
