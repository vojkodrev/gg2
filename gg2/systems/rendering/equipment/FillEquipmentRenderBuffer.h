#pragma once
#include "FillEquipmentEntityRenderBuffer.h"
#include "../../../structs/equipment/Equipment.h"
#include "../../../structs/core/constants/RenderConstants.h"
#include <cstdint>

template<int N>
inline void fillEquipmentRenderBuffer(
    RenderBuffer &rb,
    const Equipment<N> &equipment,
    uint32_t entityIndex,
    uint32_t parentRenderIndex,
    uint32_t groupId)
{
    fillEquipmentEntityRenderBuffer(
        rb,
        equipment.weapon.base,
        entityIndex,
        parentRenderIndex,
        groupId,
        WEAPON_Z_INDEX);
    if (equipment.weapon.showAmmo[entityIndex])
        fillEquipmentEntityRenderBuffer(
            rb,
            equipment.ammo.base,
            entityIndex,
            parentRenderIndex,
            groupId,
            AMMO_Z_INDEX);
}
