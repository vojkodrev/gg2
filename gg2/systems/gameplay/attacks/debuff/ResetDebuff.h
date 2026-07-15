#pragma once
#include "../../../../structs/attacks/Debuff.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/pool/ResetPool.h"
#include <cstdint>

template<int N>
void resetDebuff(Debuff<N> &debuff, uint32_t n)
{
    resetPool(debuff.pool, n);

    for (int i = 0; i < MAX_DEBUFF_SLOTS; i++)
    {
        debuff.timer[n][i] = 0.0f;
        debuff.entityType[n][i] = EntityType::None;
        debuff.entityId[n][i] = INVALID_ID;
    }
}
