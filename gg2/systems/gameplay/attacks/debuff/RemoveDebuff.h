#pragma once
#include "../../../../structs/attacks/Debuff.h"
#include "../../../../utils/pool/PoolFree.h"
#include <cstdint>

template<int N>
void removeDebuff(Debuff<N> &debuff, uint32_t n, int slot)
{
    debuff.timer[n][slot] = 0.0f;
    debuff.entityType[n][slot] = EntityType::None;
    debuff.entityId[n][slot] = INVALID_ID;
    poolFree(debuff.pool, n, slot);
}
