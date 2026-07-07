#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/core/constants/TintConstants.h"

template<int N>
inline void calculateEntityBaseTint(
    EntityBase<N> &entityBase,
    uint32_t i,
    float dt)
{
    entityBase.tint.damageTimer[i] -= dt;
    if (entityBase.tint.damageTimer[i] < 0.0f)
        entityBase.tint.damageTimer[i] = 0.0f;

    float tintR = 0.0f;
    float tintG = 0.0f;
    float tintB = 0.0f;
    float tintA = 0.0f;
    uint32_t tintCount = 0;

    auto addTint = [&](bool isActive, float r, float g, float b, float a)
    {
        if (!isActive)
            return;

        tintR += r;
        tintG += g;
        tintB += b;
        tintA += a;
        tintCount++;
    };

    addTint(entityBase.tint.damageTimer[i] > 0.0f, DAMAGE_TINT_R, DAMAGE_TINT_G, DAMAGE_TINT_B, DAMAGE_TINT_A);
    addTint(entityBase.tint.isPoisoned[i], POISON_TINT_R, POISON_TINT_G, POISON_TINT_B, POISON_TINT_A);
    addTint(entityBase.tint.isSlowed[i], SLOWED_TINT_R, SLOWED_TINT_G, SLOWED_TINT_B, SLOWED_TINT_A);

    if (tintCount == 0)
    {
        entityBase.tint.r[i] = CLEAR_TINT_R;
        entityBase.tint.g[i] = CLEAR_TINT_G;
        entityBase.tint.b[i] = CLEAR_TINT_B;
        entityBase.tint.a[i] = CLEAR_TINT_A;
        return;
    }

    const float tintWeight = 1.0f / static_cast<float>(tintCount);
    entityBase.tint.r[i] = tintR * tintWeight;
    entityBase.tint.g[i] = tintG * tintWeight;
    entityBase.tint.b[i] = tintB * tintWeight;
    entityBase.tint.a[i] = tintA * tintWeight;
}
