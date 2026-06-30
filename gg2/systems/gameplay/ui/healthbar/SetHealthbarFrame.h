#pragma once
#include "../../../structs/statistics/Statistics.h"
#include "../../../structs/ui/Healthbar.h"
#include <algorithm>
#include <cstdint>

template<int N>
inline void setHealthbarFrame(
    Healthbar<N> &healthbar,
    const Statistics<N> &statistics,
    uint32_t index)
{
    const int frameCount = healthbar.base.animation.frameCount[index];
    const int maxHp = statistics.health.maxHp[index];
    const int hp = std::clamp(statistics.health.hp[index], 0, maxHp);

    if (frameCount <= 0)
        return;

    if (maxHp <= 0)
    {
        healthbar.base.animation.frameIndex[index] = 0;
        return;
    }

    healthbar.base.animation.frameIndex[index] =
        hp * (frameCount - 1) / maxHp;
}
