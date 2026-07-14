#pragma once
#include "../../../../structs/attacks/AggroTable.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/queue/Queue.h"
#include <cstdint>

template<int N>
void resetAggroTable(AggroTable<N> &aggroTable, uint32_t n)
{
    aggroTable.pool.count[n] = 0;
    aggroTable.pool.freeQueue.head[n] = 0;
    aggroTable.pool.freeQueue.tail[n] = 0;
    aggroTable.maxValue[n] = 0.0f;
    aggroTable.maxEntityType[n] = EntityType::None;
    aggroTable.maxEntityId[n] = INVALID_ID;

    for (int i = 0; i < MAX_AGGRO_SLOTS; i++)
    {
        aggroTable.pool.active[n][i] = false;
        aggroTable.entityType[n][i] = EntityType::None;
        aggroTable.entityId[n][i] = INVALID_ID;
        aggroTable.value[n][i] = 0.0f;
    }
}
