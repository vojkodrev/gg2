#pragma once
#include "ScaleAnimationFrames.h"
#include "ScaleEntityBaseSize.h"
#include <cstdint>

template<int N>
inline void scaleEntityBase(EntityBase<N> &entityBase, uint32_t i)
{
    scaleEntityBaseSize(entityBase, i);
    scaleAnimationFrames(
        entityBase.animation,
        entityBase.scale,
        i);
}
