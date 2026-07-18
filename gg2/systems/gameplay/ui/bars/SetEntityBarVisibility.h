#pragma once
#include "../../../structs/statistics/Statistics.h"
#include "../../../structs/ui/Healthbar.h"
#include "../../../structs/ui/Manabar.h"
#include <cstdint>

template<int N>
inline void setEntityBarVisibility(
    Healthbar<N> &healthbar,
    Manabar<N> &manabar,
    const Statistics<N> &statistics,
    uint32_t index)
{
    const bool wasShowingHealthbar = healthbar.show[index];
    const bool hasMana = statistics.mana.maxMana[index] > 0;
    const bool showBars =
        statistics.health.hp[index] < statistics.health.maxHp[index] ||
        (hasMana && statistics.mana.mana[index] < statistics.mana.maxMana[index]);

    healthbar.show[index] = showBars;
    healthbar.dirty[index] =
        healthbar.dirty[index] || wasShowingHealthbar != healthbar.show[index];

    if (!hasMana)
        return;

    const bool wasShowingManabar = manabar.show[index];
    manabar.show[index] = showBars;
    manabar.dirty[index] =
        manabar.dirty[index] || wasShowingManabar != manabar.show[index];
}
