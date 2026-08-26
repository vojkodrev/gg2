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
    if (frostNovaDebuff != nullptr && frostNovaDebuff->active[entityIndex])
        return 0.0f;

    if (concussiveShotDebuff != nullptr &&
        concussiveShotDebuff->active[entityIndex])
        return moveSpeed * CONCUSSIVE_SHOT_SPEED_MULTIPLIER;

    return moveSpeed;
}
