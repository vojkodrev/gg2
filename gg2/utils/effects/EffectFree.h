#pragma once
#include "../../structs/core/Group.h"
#include "../../structs/effect/Effect.h"
#include "../groups/GroupFree.h"
#include "../pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void effectFree(Effect &effect, Group<TGroupCapacity> &groups, int effectIndex)
{
    groupFree(groups, effect.groupId[effectIndex]);
    poolFree(effect.pool, effectIndex);
}
