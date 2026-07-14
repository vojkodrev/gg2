#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "../../../../utils/pool/PoolFree.h"
#include "FindAggroTableSlotByEntityId.h"
#include "RefreshAggroTableMax.h"
#include <cstdint>

template<int N>
void removeFromAggroTableValue(
    AggroTable<N> &aggroTable,
    uint32_t n,
    EntityType entityType,
    int entityId)
{
    int slot = findAggroTableSlotByEntityId(aggroTable, n, entityType, entityId);

    if (slot == INVALID_ID)
        return;

    const bool removedMaxEntity =
        aggroTable.maxEntityType[n] == entityType &&
        aggroTable.maxEntityId[n] == entityId;
    aggroTable.value[n][slot] = 0.0f;
    aggroTable.entityType[n][slot] = EntityType::None;
    aggroTable.entityId[n][slot] = INVALID_ID;
    poolFree(aggroTable.pool, n, slot);

    if (removedMaxEntity)
        refreshAggroTableMax(aggroTable, n);
}
