#pragma once
#include <cstdint>
#include "../../../structs/core/Animation.h"

template<int N>
inline void scaleAnimationFrames(Animation<N> &animation, const float scale[N], uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        for (int f = 0; f < animation.frameCount[i]; f++)
        {
            animation.frame.anchor.offX[i][f] = animation.frame.anchor.initialOffX[i][f] * scale[i];
            animation.frame.anchor.offY[i][f] = animation.frame.anchor.initialOffY[i][f] * scale[i];
            animation.frame.anchor.w[i][f] = animation.frame.anchor.initialW[i][f] * scale[i];
            animation.frame.anchor.h[i][f] = animation.frame.anchor.initialH[i][f] * scale[i];

            animation.frame.collision.offX[i][f] = animation.frame.collision.initialOffX[i][f] * scale[i];
            animation.frame.collision.offY[i][f] = animation.frame.collision.initialOffY[i][f] * scale[i];
            animation.frame.collision.w[i][f] = animation.frame.collision.initialW[i][f] * scale[i];
            animation.frame.collision.h[i][f] = animation.frame.collision.initialH[i][f] * scale[i];
        }
    }
}
