#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/core/constants/TintConstants.h"

template<int N>
inline void clearTintWhenTimerExpires(
    EntityBase<N> &entityBase,
    uint32_t i,
    float dt)
{
    entityBase.tint.clearTimer[i] -= dt;
    if (entityBase.tint.clearTimer[i] > 0.0f)
        return;

    entityBase.tint.clearTimer[i] = 0.0f;
    entityBase.tint.r[i] = CLEAR_TINT_R;
    entityBase.tint.g[i] = CLEAR_TINT_G;
    entityBase.tint.b[i] = CLEAR_TINT_B;
    entityBase.tint.a[i] = CLEAR_TINT_A;
}
