#pragma once
#include "SetBarFrame.h"
#include "../../../structs/statistics/Statistics.h"
#include "../../../structs/ui/Healthbar.h"
#include "../../../structs/ui/Manabar.h"
#include <cstdint>

template<int N>
inline void setEntityBarFrames(
    Healthbar<N> &healthbar,
    Manabar<N> &manabar,
    const Statistics<N> &statistics,
    uint32_t index)
{
    if (healthbar.show[index] &&
        (healthbar.dirty[index] || statistics.health.dirty[index]))
        setBarFrame(
            healthbar,
            statistics.health.hp[index],
            statistics.health.maxHp[index],
            index);

    if (statistics.mana.maxMana[index] > 0 &&
        manabar.show[index] &&
        (manabar.dirty[index] || statistics.mana.dirty[index]))
        setBarFrame(
            manabar,
            statistics.mana.mana[index],
            statistics.mana.maxMana[index],
            index);
}
