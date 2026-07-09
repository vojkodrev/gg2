#pragma once
#include "../../../structs/core/Groups.h"
#include "../../../structs/effect/Effect.h"
#include "../../../utils/groups/GroupFree.h"
#include "../../../utils/pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void effectFree(Effect &effect, Groups<TGroupCapacity> &groups, int effectIndex)
{
    if (!effect.pool.active[effectIndex])
        return;

    groupFree(groups, effect.groupId[effectIndex]);
    poolFree(effect.pool, effectIndex);
}
