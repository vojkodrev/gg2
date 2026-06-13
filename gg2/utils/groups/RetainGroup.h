#pragma once
#include <cstdint>
#include "../../structs/core/Group.h"

template<uint32_t TGroupCapacity>
int retainGroup(Group<TGroupCapacity> &group, int groupId)
{
    group.count[groupId]++;
    return groupId;
}
