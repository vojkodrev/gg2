#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/core/Statistics.h"
#include "../../../structs/core/constants/TintConstants.h"

template<int N>
inline void applyDamageTint(
    EntityBase<N> &entityBase,
    const Statistics<N> &statistics,
    uint32_t i)
{
    if (!statistics.hpDirty[i] || statistics.hp[i] >= statistics.prevHp[i])
        return;

    entityBase.tint.damageTimer[i] = DAMAGE_TINT_CLEAR_TIME;
}
