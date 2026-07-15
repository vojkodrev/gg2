#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "RefreshAggroTableMax.h"
#include "RemoveFromAggroTableValue.h"
#include <cstdint>

template<int N>
void clearInactiveAggroTableEntities(
    AggroTable<N> &aggroTable,
    uint32_t n,
    const bool (&active)[N])
{
    for (int i = (int)aggroTable.pool.count[n] - 1; i >= 0; i--)
    {
        if (!aggroTable.pool.active[n][i])
            continue;

        if (aggroTable.entityType[n][i] != EntityType::NPC)
            continue;

        const int entityId = aggroTable.entityId[n][i];
        if (entityId >= 0 && entityId < N && active[entityId])
            continue;

        removeFromAggroTableValue(
            aggroTable,
            n,
            EntityType::NPC,
            entityId,
            true);
    }

    refreshAggroTableMax(aggroTable, n);
}
