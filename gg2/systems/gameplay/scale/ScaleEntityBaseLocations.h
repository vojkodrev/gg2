#pragma once
#include "../../../structs/core/EntityBase.h"
#include "ScaleAnimationFrameLocations.h"
#include <cstdint>

template<int N>
inline void scaleEntityBaseLocations(EntityBase<N> &entityBase, uint32_t i)
{
    scaleAnimationFrameLocations(
        entityBase.animation,
        entityBase.scale,
        i);
}
