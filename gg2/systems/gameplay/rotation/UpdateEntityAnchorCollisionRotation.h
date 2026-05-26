#pragma once
#include "../../../structs/core/Animation.h"
#include "UpdateAnchorRotation.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorCollisionRotation(EntityBase<N> &entityBase, uint32_t i)
{
    if (entityBase.rotation.rotate[i] == 0.0f)
        return;

    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        updateAnchorRotation(
            entityBase.animation.frame.anchor,
            entityBase,
            i,
            f);
        updateAnchorRotation(
            entityBase.animation.frame.collision,
            entityBase,
            i,
            f);
    }
}
