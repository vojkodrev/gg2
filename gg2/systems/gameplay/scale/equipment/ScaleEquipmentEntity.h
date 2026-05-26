#pragma once
#include "../ScaleEntityBase.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void scaleEquipmentEntity(
    EntityBase<1> &playerEquipmentBase,
    EntityBase<N> &npcEquipmentBase,
    uint32_t npcCount)
{
    scaleEntityBase(playerEquipmentBase, 0);

    for (uint32_t i = 0; i < npcCount; i++)
        scaleEntityBase(npcEquipmentBase, i);
}
