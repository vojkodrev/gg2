#include "DebugRenderPlayer.h"
#include "RenderColBox.h"
#include "DebugRenderEquipment.h"
#include "../../../utils/rect/EntityBaseAnchorAABB.h"
#include "../../../utils/collision/EntityBaseColAABB.h"

void debugRenderPlayer(const Context &ctx)
{
    SDL_Renderer *renderer = ctx.renderer;
    const auto &player = ctx.data.player;
    const bool showCollision = ctx.data.debug.showCollision;

    if (showCollision)
    {
        SDL_FRect col = entityBaseColAABB(player.base, 0);
        if (col.w > 0.0f && col.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            renderColBox(ctx, col);
        }

        SDL_FRect anchor = entityBaseAnchorAABB(player.base, 0);
        if (anchor.w > 0.0f && anchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            renderColBox(ctx, anchor);
        }
    }

    debugRenderEquipment(ctx, player.equipment, 0);
}
