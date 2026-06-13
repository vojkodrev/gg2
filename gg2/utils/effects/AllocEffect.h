#pragma once
#include "../../structs/core/Group.h"
#include "../../structs/effect/Effect.h"
#include "../groups/RetainGroup.h"
#include "../pool/PoolAlloc.h"

template<uint32_t TGroupCapacity>
int allocEffect(Effect &effect, Group<TGroupCapacity> &groups, int groupId)
{
    int effectIndex = poolAlloc(effect.pool);
    if (effectIndex == -1)
        return -1;

    effect.groupId[effectIndex] = retainGroup(groups, groupId);
    return effectIndex;
}
