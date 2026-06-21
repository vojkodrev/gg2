#pragma once
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void cleanupEntityBase(EntityBase<N> &entityBase, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        entityBase.position.dirty[i] = false;
        entityBase.facing.dirty[i] = false;
    }
}
