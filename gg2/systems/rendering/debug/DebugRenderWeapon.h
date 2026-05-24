#pragma once
#include "Context.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityWeaponColAABB.h"
#include "../../../utils/rect/EntityWeaponAnchorAABB.h"

template<int N>
inline void debugRenderWeapon(const Context &ctx, const Weapon<N> &weapon, uint32_t i)
{
    if (!ctx.data.debug.showWeaponCollision)
        return;

    SDL_FRect weaponCol = entityWeaponColAABB(weapon, i);
    if (weaponCol.w > 0.0f && weaponCol.h > 0.0f)
    {
        SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 0, 255);
        renderColBox(ctx, weaponCol);
    }

    SDL_FRect weaponAnchor = entityWeaponAnchorAABB(weapon, i);
    if (weaponAnchor.w > 0.0f && weaponAnchor.h > 0.0f)
    {
        SDL_SetRenderDrawColor(ctx.renderer, 0, 255, 255, 255);
        renderColBox(ctx, weaponAnchor);
    }
}
