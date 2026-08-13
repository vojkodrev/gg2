#pragma once
#include "../../../structs/groups/Groups.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/effect/Effect.h"
#include "../../../utils/groups/GroupRetain.h"
#include "../../../utils/pool/PoolAlloc.h"
#include "../../../utils/pool/PoolFree.h"

template<uint32_t TGroupCapacity>
int effectAlloc(Effect &effect, Groups<TGroupCapacity> &groups, int groupId)
{
    if (groupId < 0 || !groups.pool.active[0][groupId])
        return INVALID_ID;

    int effectIndex = poolAlloc(effect.pool, 0);
    if (effectIndex == INVALID_ID)
        return INVALID_ID;

    const int retainedGroupId = groupRetain(groups, groupId);
    if (retainedGroupId == INVALID_ID)
    {
        poolFree(effect.pool, 0, effectIndex);
        return INVALID_ID;
    }

    effect.groupId[effectIndex] = retainedGroupId;
    return effectIndex;
}
