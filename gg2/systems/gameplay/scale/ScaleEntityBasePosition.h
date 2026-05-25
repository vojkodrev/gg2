#pragma once
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void scaleEntityBasePosition(EntityBase<N> &entityBase, uint32_t i)
{
    entityBase.position.w[i] = entityBase.position.initialW[i] * entityBase.scale[i];
    entityBase.position.h[i] = entityBase.position.initialH[i] * entityBase.scale[i];
}
