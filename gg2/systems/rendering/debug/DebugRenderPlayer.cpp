#include "DebugRenderPlayer.h"
#include "RenderColBox.h"
#include "DebugRenderWeapon.h"
#include "../../../utils/rect/EntityAnchorAABBPlayer.h"
#include "../../../utils/collision/EntityColAABBPlayer.h"

void debugRenderPlayer(const Context &ctx)
{
    SDL_Renderer *renderer = ctx.renderer;
    const auto &player = ctx.data.player;
    const bool showCollision = ctx.data.debug.showCollision;

    if (showCollision)
    {
        SDL_FRect col = entityColAABB(player);
        if (col.w > 0.0f && col.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            renderColBox(ctx, col);
        }

        SDL_FRect anchor = entityAnchorAABB(player);
        if (anchor.w > 0.0f && anchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            renderColBox(ctx, anchor);
        }
    }

    debugRenderWeapon(ctx, player.equipment.weapon, 0);
}
