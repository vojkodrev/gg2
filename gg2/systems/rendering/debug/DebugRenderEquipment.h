#pragma once
#include "Context.h"
#include "DebugRenderEntityBase.h"
#include "RenderColBox.h"
#include "../../../structs/equipment/Equipment.h"
#include "../../../structs/equipment/WeaponType.h"

template<int N>
inline void debugRenderEquipment(const Context &ctx, const Equipment<N> &equipment, uint32_t i)
{
    if (!equipment.weapon.exists[i])
        return;

    if (ctx.data.debug.showWeaponCollision)
    {
        debugRenderEntityBase(ctx, equipment.weapon.base, i, SDL_Color{0, 255, 255, 255});

        const int frameIndex = equipment.weapon.base.animation.frameIndex[i];
        SDL_FRect ammoAnchor = {
            equipment.weapon.base.position.x[i] + equipment.weapon.ranged.ammoAnchor.offX[i][frameIndex],
            equipment.weapon.base.position.y[i] + equipment.weapon.ranged.ammoAnchor.offY[i][frameIndex],
            equipment.weapon.ranged.ammoAnchor.w[i][frameIndex],
            equipment.weapon.ranged.ammoAnchor.h[i][frameIndex]
        };

        if (ammoAnchor.w > 0.0f && ammoAnchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderColBox(ctx, ammoAnchor);
        }
    }

    if (
        ctx.data.debug.showAmmoCollision &&
        equipment.ammo.exists[i] &&
        equipment.weapon.type[i] == WeaponType::Ranged &&
        equipment.weapon.ranged.showAmmo[i])
        debugRenderEntityBase(ctx, equipment.ammo.base, i, SDL_Color{255, 255, 0, 255});
}
