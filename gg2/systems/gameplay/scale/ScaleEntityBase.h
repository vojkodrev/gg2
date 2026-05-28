#pragma once
#include "ScaleAnimationFrames.h"
#include "ScaleEntityBasePosition.h"
#include <cstdint>

template<int N>
inline void scaleEntityBase(EntityBase<N> &entityBase, uint32_t i)
{
    scaleEntityBasePosition(entityBase, i);
    scaleAnimationFrames(
        entityBase.animation,
        entityBase.scale,
        i);
}
