#pragma once
#include "../../structs/attacks/Debuff.h"
#include "../../structs/core/constants/ConcussiveShotConstants.h"
#include <cstdint>

template<int N>
inline float getEntityMovementSpeed(
    const Debuff<N> *concussiveShotDebuff,
    const Debuff<N> *frostNovaDebuff,
    uint32_t entityIndex,
    float moveSpeed)
{
    if (frostNovaDebuff != nullptr)
    {
        for (uint32_t i = 0; i < MAX_DEBUFF_SLOTS; i++)
        {
            if (frostNovaDebuff->pool.active[entityIndex][i])
                return 0.0f;
        }
    }

    if (concussiveShotDebuff != nullptr)
    {
        for (uint32_t i = 0; i < MAX_DEBUFF_SLOTS; i++)
        {
            if (concussiveShotDebuff->pool.active[entityIndex][i])
                return moveSpeed * CONCUSSIVE_SHOT_SPEED_MULTIPLIER;
        }
    }

    return moveSpeed;
}
