#pragma once
#include "../../../structs/core/EntityBase.h"
#include "ScaleAnchorLocation.h"
#include <cstdint>

template<int N>
inline void scaleEntityBaseLocations(EntityBase<N> &entityBase, uint32_t i)
{
    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        scaleAnchorLocation(entityBase.animation.frame.anchor, entityBase.scale[i], i, f);
        scaleAnchorLocation(entityBase.animation.frame.collision, entityBase.scale[i], i, f);
    }
}
