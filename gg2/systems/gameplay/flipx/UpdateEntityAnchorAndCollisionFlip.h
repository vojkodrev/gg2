#pragma once
#include "../../../structs/core/Animation.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorAndCollisionFlip(Animation<N> &animation, uint32_t i, float entityW, bool flipX)
{
    if (!flipX)
        return;

    for (int f = 0; f < animation.frameCount[i]; f++)
    {
        animation.frame.anchor.offX[i][f] = entityW - animation.frame.anchor.offX[i][f] - animation.frame.anchor.w[i][f];
        animation.frame.collision.offX[i][f] = entityW - animation.frame.collision.offX[i][f] - animation.frame.collision.w[i][f];
    }
}
