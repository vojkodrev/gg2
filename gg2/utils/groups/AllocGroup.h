#pragma once
#include <cstdint>
#include "../../structs/core/Group.h"
#include "../pool/PoolAlloc.h"

template<uint32_t TGroupCapacity>
int allocGroup(Group<TGroupCapacity> &group)
{
    int index = poolAlloc(group.pool);
    if (index == -1)
        return -1;

    group.count[index] = 1;
    return index;
}
