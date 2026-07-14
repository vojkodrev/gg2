#pragma once
#include <cstdint>
#include "../../structs/core/Groups.h"
#include "../pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void groupFree(Groups<TGroupCapacity> &groups, int groupId)
{
    if (!groups.pool.active[0][groupId] || groups.count[groupId] == 0)
        return;

    groups.count[groupId]--;

    if (groups.count[groupId] == 0)
        poolFree(groups.pool, 0, groupId);
}
