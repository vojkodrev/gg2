#include "DebugRenderPlayer.h"
#include "RenderColBox.h"
#include "../../../utils/rect/EntityAnchorAABBPlayer.h"
#include "../../../utils/rect/EntityWeaponAnchorAABBPlayer.h"
#include "../../../utils/collision/EntityColAABBPlayer.h"
#include "../../../utils/collision/EntityWeaponColAABBPlayer.h"

void debugRenderPlayer(const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_Renderer *renderer = ctx.renderer;
    const auto &player = ctx.data.player;
    const bool showCollision = ctx.data.debug.showCollision;
    const bool showWeaponCollision = ctx.data.debug.showWeaponCollision;

    if (showCollision)
    {
        SDL_FRect col = entityColAABB(player);
        if (col.w > 0.0f && col.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            renderColBox(renderer, col, off, screen);
        }

        SDL_FRect anchor = entityAnchorAABB(player);
        if (anchor.w > 0.0f && anchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            renderColBox(renderer, anchor, off, screen);
        }
    }

    if (showWeaponCollision)
    {
        SDL_FRect weaponCol = entityWeaponColAABB(player);
        if (weaponCol.w > 0.0f && weaponCol.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            renderColBox(renderer, weaponCol, off, screen);
        }

        SDL_FRect weaponAnchor = entityWeaponAnchorAABB(player);
        if (weaponAnchor.w > 0.0f && weaponAnchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            renderColBox(renderer, weaponAnchor, off, screen);
        }
    }
}
