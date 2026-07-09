#pragma once
#include "../../../structs/core/Groups.h"
#include "../../../structs/effect/Effect.h"
#include "../../../utils/groups/GroupRetain.h"
#include "../../../utils/pool/PoolAlloc.h"
#include "../../../utils/pool/PoolFree.h"

template<uint32_t TGroupCapacity>
int effectAlloc(Effect &effect, Groups<TGroupCapacity> &groups, int groupId)
{
    if (groupId < 0 || !groups.pool.active[groupId])
        return -1;

    int effectIndex = poolAlloc(effect.pool);
    if (effectIndex == -1)
        return -1;

    const int retainedGroupId = groupRetain(groups, groupId);
    if (retainedGroupId == -1)
    {
        poolFree(effect.pool, effectIndex);
        return -1;
    }

    effect.groupId[effectIndex] = retainedGroupId;
    return effectIndex;
}
