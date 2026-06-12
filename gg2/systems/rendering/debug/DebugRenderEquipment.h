#pragma once
#include "Context.h"
#include "DebugRenderEntityBase.h"
#include "RenderColBox.h"
#include "../../../structs/equipment/Equipment.h"

template<int N>
inline void debugRenderEquipment(const Context &ctx, const Equipment<N> &equipment, uint32_t i)
{
    if (ctx.data.debug.showWeaponCollision)
    {
        debugRenderEntityBase(ctx, equipment.weapon.base, i, SDL_Color{0, 255, 255, 255});

        SDL_FRect ammoAnchor = {
            equipment.weapon.base.position.x[i] + equipment.weapon.ammoAnchor.offX[i][0],
            equipment.weapon.base.position.y[i] + equipment.weapon.ammoAnchor.offY[i][0],
            equipment.weapon.ammoAnchor.w[i][0],
            equipment.weapon.ammoAnchor.h[i][0]
        };

        if (ammoAnchor.w > 0.0f && ammoAnchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderColBox(ctx, ammoAnchor);
        }
    }

    if (ctx.data.debug.showAmmoCollision && equipment.weapon.hasAmmo[i] && equipment.weapon.showAmmo[i])
        debugRenderEntityBase(ctx, equipment.ammo.base, i, SDL_Color{255, 255, 0, 255});
}
