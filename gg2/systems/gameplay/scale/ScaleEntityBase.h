#pragma once
#include "ScaleAnimationFrameLocations.h"
#include "ScaleAnimationFrameSizes.h"
#include "ScaleEntityBaseSize.h"
#include <cstdint>

template<int N>
inline void scaleEntityBase(EntityBase<N> &entityBase, uint32_t i)
{
    scaleEntityBaseSize(entityBase, i);
    scaleAnimationFrameLocations(
        entityBase.animation,
        entityBase.scale,
        i);
    scaleAnimationFrameSizes(
        entityBase.animation,
        entityBase.scale,
        i);
}
