#pragma once
#include <cstdint>
#include "../../structs/core/Group.h"
#include "../pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void freeGroup(Group<TGroupCapacity> &group, int groupId)
{
    group.count[groupId]--;

    if (group.count[groupId] == 0)
        poolFree(group.pool, groupId);
}
