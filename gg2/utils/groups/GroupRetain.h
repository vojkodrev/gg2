#pragma once
#include <cstdint>
#include "../../structs/core/Groups.h"

template<uint32_t TGroupCapacity>
int groupRetain(Groups<TGroupCapacity> &groups, int groupId)
{
    if (groupId < 0 || !groups.pool.active[groupId])
        return -1;

    groups.count[groupId]++;
    return groupId;
}
