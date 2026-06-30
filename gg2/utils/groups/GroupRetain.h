#pragma once
#include <cstdint>
#include "../../structs/core/Group.h"

template<uint32_t TGroupCapacity>
int groupRetain(Group<TGroupCapacity> &group, int groupId)
{
    if (groupId < 0 || !group.pool.active[groupId])
        return -1;

    group.count[groupId]++;
    return groupId;
}
