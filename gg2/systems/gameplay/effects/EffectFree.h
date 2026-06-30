#pragma once
#include "../../../structs/core/Group.h"
#include "../../../structs/effect/Effect.h"
#include "../../../utils/groups/GroupFree.h"
#include "../../../utils/pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void effectFree(Effect &effect, Group<TGroupCapacity> &groups, int effectIndex)
{
    if (!effect.pool.active[effectIndex])
        return;

    groupFree(groups, effect.groupId[effectIndex]);
    poolFree(effect.pool, effectIndex);
}
