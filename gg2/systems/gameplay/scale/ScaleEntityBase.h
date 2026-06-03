#pragma once
#include "ScaleEntityBaseLocations.h"
#include "ScaleEntityBaseSizes.h"
#include <cstdint>

template<int N>
inline void scaleEntityBase(EntityBase<N> &entityBase, uint32_t i)
{
    scaleEntityBaseLocations(entityBase, i);
    scaleEntityBaseSizes(entityBase, i);
}
