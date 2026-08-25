#pragma once
#include "../../../structs/groups/Groups.h"
#include "../../../structs/effect/Effect.h"
#include "../../../utils/groups/GroupFree.h"
#include "../../../utils/pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void effectFree(Effect &effect, Groups<TGroupCapacity> &groups, int effectIndex)
{
    if (!effect.pool.active[0][effectIndex])
        return;

    groupFree(groups, effect.group.id[effectIndex]);
    poolFree(effect.pool, 0, effectIndex);
}
