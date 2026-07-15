#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/pool/PoolAlloc.h"
#include "FindAggroTableSlotByEntityId.h"
#include "RefreshAggroTableMax.h"
#include <cstdint>

template<int N>
void addToAggroTableValue(
    AggroTable<N> &aggroTable,
    uint32_t n,
    EntityType entityType,
    int entityId,
    float value)
{
    int slot = findAggroTableSlotByEntityId(aggroTable, n, entityType, entityId);

    if (slot == INVALID_ID)
    {
        slot = poolAlloc(aggroTable.pool, n);
        if (slot == INVALID_ID)
            return;

        aggroTable.entityType[n][slot] = entityType;
        aggroTable.entityId[n][slot] = entityId;
    }

    const bool replacedMaxEntity =
        aggroTable.maxEntityType[n] == entityType &&
        aggroTable.maxEntityId[n] == entityId;
    aggroTable.value[n][slot] += value;
    const float nextValue = aggroTable.value[n][slot];

    if (aggroTable.maxEntityId[n] == INVALID_ID || nextValue >= aggroTable.maxValue[n])
    {
        aggroTable.maxValue[n] = nextValue;
        aggroTable.maxEntityType[n] = entityType;
        aggroTable.maxEntityId[n] = entityId;
        return;
    }

    if (replacedMaxEntity)
        refreshAggroTableMax(aggroTable, n);
}
