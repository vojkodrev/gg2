#pragma once
#include "Context.h"
#include "DebugRenderEquipmentEntity.h"
#include "../../../structs/equipment/Equipment.h"

template<int N>
inline void debugRenderEquipment(const Context &ctx, const Equipment<N> &equipment, uint32_t i)
{
    if (ctx.data.debug.showWeaponCollision)
        debugRenderEquipmentEntity(ctx, equipment.weapon.base, i, SDL_Color{0, 255, 255, 255});

    if (ctx.data.debug.showAmmoCollision)
        debugRenderEquipmentEntity(ctx, equipment.ammo.base, i, SDL_Color{255, 255, 0, 255});
}
