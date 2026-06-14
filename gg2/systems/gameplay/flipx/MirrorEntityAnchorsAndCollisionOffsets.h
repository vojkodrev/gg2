#pragma once
#include "../../../structs/core/EntityBase.h"
#include "MirrorAnchorOffsetX.h"
#include <cstdint>

template<int N>
inline void mirrorEntityAnchorsAndCollisionOffsets(EntityBase<N> &entityBase, uint32_t i)
{
    if (!entityBase.facing.flipX[i])
        return;

    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        mirrorAnchorOffsetX(entityBase.animation.frame.anchor, entityBase.position.w[i], i, f);
        mirrorAnchorOffsetX(entityBase.animation.frame.collision, entityBase.position.w[i], i, f);
    }
}
