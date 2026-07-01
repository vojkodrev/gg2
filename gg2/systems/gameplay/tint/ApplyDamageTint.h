#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/statistics/Statistics.h"
#include "../../../structs/core/constants/TintConstants.h"

template<int N>
inline void applyDamageTint(
    EntityBase<N> &entityBase,
    const Statistics<N> &statistics,
    uint32_t i)
{
    if (!statistics.health.dirty[i] || statistics.health.hp[i] >= statistics.health.prevHp[i])
        return;

    entityBase.tint.damageTimer[i] = DAMAGE_TINT_CLEAR_TIME;
}
