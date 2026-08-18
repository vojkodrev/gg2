#pragma once
#include "Context.h"
#include "DebugRenderEntityBase.h"
#include "RenderColBox.h"
#include "../../../structs/equipment/Equipment.h"
#include "../../../structs/equipment/WeaponType.h"

template<int N>
inline void debugRenderEquipment(
    const Context &ctx,
    const Equipment<N> &equipment,
    uint32_t entityIndex)
{
    if (!equipment.weapon.exists[entityIndex])
        return;

    if (ctx.data.debug.showWeaponCollision)
    {
        debugRenderEntityBase(
            ctx,
            equipment.weapon.base,
            entityIndex,
            SDL_Color{0, 255, 255, 255});

        const int frameIndex =
            equipment.weapon.base.animation.frameIndex[entityIndex];
        SDL_FRect ammoAnchor = {
            equipment.weapon.base.position.x[entityIndex] +
                equipment.weapon.ranged.ammoAnchor
                    .offX[entityIndex][frameIndex][0],
            equipment.weapon.base.position.y[entityIndex] +
                equipment.weapon.ranged.ammoAnchor
                    .offY[entityIndex][frameIndex][0],
            equipment.weapon.ranged.ammoAnchor
                .w[entityIndex][frameIndex][0],
            equipment.weapon.ranged.ammoAnchor
                .h[entityIndex][frameIndex][0]
        };

        if (ammoAnchor.w > 0.0f && ammoAnchor.h > 0.0f)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderColBox(ctx, ammoAnchor);
        }
    }

    if (
        ctx.data.debug.showAmmoCollision &&
        equipment.ammo.exists[entityIndex] &&
        equipment.weapon.type[entityIndex] == WeaponType::Ranged &&
        equipment.weapon.ranged.showAmmo[entityIndex])
        debugRenderEntityBase(
            ctx,
            equipment.ammo.base,
            entityIndex,
            SDL_Color{255, 255, 0, 255});
}
