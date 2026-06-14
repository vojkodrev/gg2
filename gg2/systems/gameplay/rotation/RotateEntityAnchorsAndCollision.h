#pragma once
#include "../../../structs/core/Animation.h"
#include "RotateAnchorAroundEntityCenter.h"
#include <cstdint>

template<int N>
inline void rotateEntityAnchorsAndCollision(EntityBase<N> &entityBase, uint32_t i)
{
    if (entityBase.rotation.rotate[i] == 0.0f)
        return;

    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        rotateAnchorAroundEntityCenter(
            entityBase.animation.frame.anchor,
            entityBase,
            i,
            f);
        rotateAnchorAroundEntityCenter(
            entityBase.animation.frame.collision,
            entityBase,
            i,
            f);
    }
}
