#pragma once
#include "Context.h"
#include "DebugRenderEntityBase.h"
#include "RenderColBox.h"
#include "RenderColCenter.h"
#include "../../../structs/equipment/Equipment.h"
#include "../../../structs/equipment/WeaponType.h"

template<int N>
inline void debugRenderEquipment(const Context &ctx, const Equipment<N> &equipment, uint32_t i)
{
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
        ctx.data.debug.showRangedWeaponCollision &&
        equipment.weapon.type[i] == WeaponType::Ranged)
    {
        const int frameIndex = equipment.weapon.base.animation.frameIndex[i];
        const auto &ranged = equipment.weapon.ranged;
        if (ranged.entityCollision.hasAnchor[i][frameIndex])
        {
            const SDL_FRect collision = {
                equipment.weapon.base.position.x[i] + ranged.entityCollision.offX[i][frameIndex],
                equipment.weapon.base.position.y[i] + ranged.entityCollision.offY[i][frameIndex],
                ranged.entityCollision.w[i][frameIndex],
                ranged.entityCollision.h[i][frameIndex]
            };
            SDL_SetRenderDrawColor(ctx.renderer, 0, 255, 128, 255);
            renderColBox(ctx, collision);

            const SDL_FPoint center = {
                collision.x + ranged.entityCollisionCenter.x[i][frameIndex],
                collision.y + ranged.entityCollisionCenter.y[i][frameIndex]
            };
            SDL_SetRenderDrawColor(ctx.renderer, 255, 64, 64, 255);
            renderColCenter(ctx, center, 4.0f);
        }
    }

    if (
        ctx.data.debug.showAmmoCollision &&
        equipment.weapon.type[i] == WeaponType::Ranged &&
        equipment.weapon.ranged.showAmmo[i])
        debugRenderEntityBase(ctx, equipment.ammo.base, i, SDL_Color{255, 255, 0, 255});
}
