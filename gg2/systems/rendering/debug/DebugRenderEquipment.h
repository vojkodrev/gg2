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
        const auto &ammoAnchorData = equipment.weapon.ranged.ammoAnchor;
        if (ammoAnchorData.exists[entityIndex][frameIndex][0])
        {
            const SDL_FRect ammoAnchor = {
                equipment.weapon.base.position.x[entityIndex] +
                    ammoAnchorData.offX[entityIndex][frameIndex][0],
                equipment.weapon.base.position.y[entityIndex] +
                    ammoAnchorData.offY[entityIndex][frameIndex][0],
                ammoAnchorData.w[entityIndex][frameIndex][0],
                ammoAnchorData.h[entityIndex][frameIndex][0]
            };
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderColBox(ctx, ammoAnchor);
        }

        const auto &spellAnchorData = equipment.weapon.magic.spellAnchor;
        if (spellAnchorData.exists[entityIndex][frameIndex][0])
        {
            const SDL_FRect spellAnchor = {
                equipment.weapon.base.position.x[entityIndex] +
                    spellAnchorData.offX[entityIndex][frameIndex][0],
                equipment.weapon.base.position.y[entityIndex] +
                    spellAnchorData.offY[entityIndex][frameIndex][0],
                spellAnchorData.w[entityIndex][frameIndex][0],
                spellAnchorData.h[entityIndex][frameIndex][0]
            };
            SDL_SetRenderDrawColor(ctx.renderer, 128, 128, 255, 255);
            renderColBox(ctx, spellAnchor);
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
