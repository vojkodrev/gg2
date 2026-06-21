#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/core/Statistics.h"
#include "../../../structs/core/constants/TintConstants.h"
#include <cstdint>

template<int N>
inline void applyDamageTint(
    EntityBase<N> &entityBase,
    const Statistics<N> &statistics,
    uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        if (!statistics.hpDirty[i] || statistics.hp[i] >= statistics.prevHp[i])
            continue;

        entityBase.tint.r[i] = DAMAGE_TINT_R;
        entityBase.tint.g[i] = DAMAGE_TINT_G;
        entityBase.tint.b[i] = DAMAGE_TINT_B;
        entityBase.tint.a[i] = DAMAGE_TINT_A;
        entityBase.tint.clearTimer[i] = DAMAGE_TINT_CLEAR_TIME;
    }
}
