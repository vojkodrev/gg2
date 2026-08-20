#pragma once
#include "../../structs/attacks/Debuff.h"
#include "../../structs/core/constants/ConcussiveShotConstants.h"
#include <cstdint>

template<int N>
inline float getEntityMovementSpeed(
    const Debuff<N> &debuff,
    uint32_t entityIndex,
    float moveSpeed)
{
    for (uint32_t i = 0; i < MAX_DEBUFF_SLOTS; i++)
    {
        if (debuff.pool.active[entityIndex][i])
            return moveSpeed * CONCUSSIVE_SHOT_SPEED_MULTIPLIER;
    }

    return moveSpeed;
}
