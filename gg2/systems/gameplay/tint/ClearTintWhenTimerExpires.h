#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/core/constants/TintConstants.h"
#include <cstdint>

template<int N>
inline void clearTintWhenTimerExpires(
    EntityBase<N> &entityBase,
    uint32_t count,
    float dt,
    const bool *active = nullptr)
{
    for (uint32_t i = 0; i < count; i++)
    {
        if (active != nullptr && !active[i])
            continue;

        entityBase.tint.clearTimer[i] -= dt;
        if (entityBase.tint.clearTimer[i] > 0.0f)
            continue;

        entityBase.tint.clearTimer[i] = 0.0f;
        entityBase.tint.r[i] = CLEAR_TINT_R;
        entityBase.tint.g[i] = CLEAR_TINT_G;
        entityBase.tint.b[i] = CLEAR_TINT_B;
        entityBase.tint.a[i] = CLEAR_TINT_A;
    }
}
