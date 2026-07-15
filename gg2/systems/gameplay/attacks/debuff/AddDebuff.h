#pragma once
#include "../../../../structs/attacks/Debuff.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/pool/PoolAlloc.h"
#include <cstdint>

template<int N>
void addDebuff(
    Debuff<N> &debuff,
    uint32_t n,
    EntityType entityType,
    int entityId,
    float timer)
{
    int slot = INVALID_ID;
    for (uint32_t i = 0; i < debuff.pool.count[n]; i++)
    {
        if (!debuff.pool.active[n][i])
            continue;

        if (debuff.entityType[n][i] == entityType &&
            debuff.entityId[n][i] == entityId)
        {
            slot = (int)i;
            break;
        }
    }

    if (slot == INVALID_ID)
        slot = poolAlloc(debuff.pool, n);

    if (slot == INVALID_ID)
        return;

    debuff.timer[n][slot] = timer;
    debuff.entityType[n][slot] = entityType;
    debuff.entityId[n][slot] = entityId;
}
