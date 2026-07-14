#pragma once
#include <cstdint>
#include "../../structs/core/Groups.h"
#include "../../structs/core/constants/IndexConstants.h"

template<uint32_t TGroupCapacity>
int groupRetain(Groups<TGroupCapacity> &groups, int groupId)
{
    if (groupId < 0 || !groups.pool.active[0][groupId])
        return INVALID_ID;

    groups.count[groupId]++;
    return groupId;
}
