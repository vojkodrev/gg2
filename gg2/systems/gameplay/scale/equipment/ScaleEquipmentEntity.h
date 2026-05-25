#pragma once
#include "../ScaleEntityBase.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void scaleEquipmentEntity(
    EntityBase<1> &playerBase,
    EntityBase<N> &npcBase,
    uint32_t npcCount)
{
    scaleEntityBase(playerBase, 0);

    for (uint32_t i = 0; i < npcCount; i++)
        scaleEntityBase(npcBase, i);
}
