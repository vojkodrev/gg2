#pragma once
#include "../../../structs/core/EntityBase.h"
#include "ScaleAnimationFrameSizes.h"
#include "ScaleEntityBasePositionSize.h"
#include <cstdint>

template<int N>
inline void scaleEntityBaseSizes(EntityBase<N> &entityBase, uint32_t i)
{
    scaleEntityBasePositionSize(entityBase, i);

    scaleAnimationFrameSizes(
        entityBase.animation,
        entityBase.scale,
        i);
}
