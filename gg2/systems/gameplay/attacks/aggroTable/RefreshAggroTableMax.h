#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include <cstdint>

template<int N>
void refreshAggroTableMax(AggroTable<N> &aggroTable, uint32_t n)
{
    float maxValue = 0.0f;
    EntityType maxEntityType = EntityType::None;
    int maxEntityId = INVALID_ID;

    for (uint32_t i = 0; i < aggroTable.pool.count[n]; i++)
    {
        if (!aggroTable.pool.active[n][i])
            continue;

        if (maxEntityId != INVALID_ID && aggroTable.value[n][i] <= maxValue)
            continue;

        maxValue = aggroTable.value[n][i];
        maxEntityType = aggroTable.entityType[n][i];
        maxEntityId = aggroTable.entityId[n][i];
    }

    aggroTable.maxValue[n] = maxValue;
    aggroTable.maxEntityType[n] = maxEntityType;
    aggroTable.maxEntityId[n] = maxEntityId;
}
