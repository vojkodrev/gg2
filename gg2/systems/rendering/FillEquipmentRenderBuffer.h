#pragma once
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/equipment/Equipment.h"
#include "../../structs/equipment/WeaponType.h"
#include "../../structs/core/constants/RenderConstants.h"
#include <cstdint>

template<int N>
inline void fillEquipmentRenderBuffer(
    RenderBuffer &rb,
    const Equipment<N> &equipment,
    uint32_t entityIndex,
    uint32_t groupId)
{
    if (!equipment.weapon.exists[entityIndex])
        return;

    fillEntityBaseRenderBuffer(
        rb,
        equipment.weapon.base,
        entityIndex,
        groupId,
        WEAPON_Z_INDEX);
    if (equipment.ammo.exists[entityIndex] &&
        equipment.weapon.type[entityIndex] == WeaponType::Ranged &&
        equipment.weapon.ranged.showAmmo[entityIndex])
    {
        fillEntityBaseRenderBuffer(
            rb,
            equipment.ammo.base,
            entityIndex,
            groupId,
            AMMO_Z_INDEX);
    }
}
