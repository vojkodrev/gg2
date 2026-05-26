#pragma once
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorCollisionOffsetFlip(EntityBase<N> &entityBase, uint32_t i)
{
    if (!entityBase.facing.flipX[i])
        return;

    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        entityBase.animation.frame.anchor.offX[i][f] =
            entityBase.position.w[i] - entityBase.animation.frame.anchor.offX[i][f] - entityBase.animation.frame.anchor.w[i][f];
        entityBase.animation.frame.collision.offX[i][f] =
            entityBase.position.w[i] - entityBase.animation.frame.collision.offX[i][f] - entityBase.animation.frame.collision.w[i][f];
    }
}
