#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "ClearInactiveAggroTableEntities.h"
#include <cstdint>

template<int N>
void clearInactiveAggroTableEntitiesIfMaxInactive(
    AggroTable<N> &aggroTable,
    uint32_t n,
    const bool (&active)[N])
{
    if (aggroTable.maxEntityType[n] != EntityType::NPC ||
        active[aggroTable.maxEntityId[n]])
        return;

    clearInactiveAggroTableEntities(aggroTable, n, active);
}
