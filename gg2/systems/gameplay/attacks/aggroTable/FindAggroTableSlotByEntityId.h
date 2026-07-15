#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include <cstdint>

template<int N>
int findAggroTableSlotByEntityId(
    AggroTable<N> &aggroTable,
    uint32_t n,
    EntityType entityType,
    int entityId)
{
    for (uint32_t i = 0; i < aggroTable.pool.count[n]; i++)
    {
        if (!aggroTable.pool.active[n][i])
            continue;

        if (aggroTable.entityType[n][i] != entityType)
            continue;

        if (aggroTable.entityId[n][i] != entityId)
            continue;

        return (int)i;
    }

    return INVALID_ID;
}
