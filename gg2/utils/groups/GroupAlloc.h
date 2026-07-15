#pragma once
#include <cstdint>
#include "../../structs/core/Groups.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "../pool/PoolAlloc.h"

template<uint32_t TGroupCapacity>
int groupAlloc(Groups<TGroupCapacity> &groups)
{
    int index = poolAlloc(groups.pool, 0);
    if (index == INVALID_ID)
        return INVALID_ID;

    groups.count[index] = 1;
    return index;
}
