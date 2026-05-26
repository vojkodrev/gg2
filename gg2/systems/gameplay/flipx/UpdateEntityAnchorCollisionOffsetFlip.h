#pragma once
#include "../../../structs/core/EntityBase.h"
#include "UpdateAnchorOffsetFlip.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorCollisionOffsetFlip(EntityBase<N> &entityBase, uint32_t i)
{
    if (!entityBase.facing.flipX[i])
        return;

    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        updateAnchorOffsetFlip(entityBase.animation.frame.anchor, entityBase.position.w[i], i, f);
        updateAnchorOffsetFlip(entityBase.animation.frame.collision, entityBase.position.w[i], i, f);
    }
}
