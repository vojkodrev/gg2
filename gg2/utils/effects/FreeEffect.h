#pragma once
#include "../../structs/core/Group.h"
#include "../../structs/effect/Effect.h"
#include "../groups/FreeGroup.h"
#include "../pool/PoolFree.h"

template<uint32_t TGroupCapacity>
void freeEffect(Effect &effect, Group<TGroupCapacity> &groups, int effectIndex)
{
    freeGroup(groups, effect.groupId[effectIndex]);
    poolFree(effect.pool, effectIndex);
}
