#pragma once
#include <cstdint>
#include "../../structs/core/Groups.h"
#include "../pool/PoolAlloc.h"

template<uint32_t TGroupCapacity>
int groupAlloc(Groups<TGroupCapacity> &groups)
{
    int index = poolAlloc(groups.pool);
    if (index == -1)
        return -1;

    groups.count[index] = 1;
    return index;
}
