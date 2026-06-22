#pragma once
#include "../../../structs/core/Group.h"
#include "../../../structs/effect/Effect.h"
#include "../../../utils/groups/GroupRetain.h"
#include "../../../utils/pool/PoolAlloc.h"

template<uint32_t TGroupCapacity>
int effectAlloc(Effect &effect, Group<TGroupCapacity> &groups, int groupId)
{
    int effectIndex = poolAlloc(effect.pool);
    if (effectIndex == -1)
        return -1;

    effect.groupId[effectIndex] = groupRetain(groups, groupId);
    return effectIndex;
}
