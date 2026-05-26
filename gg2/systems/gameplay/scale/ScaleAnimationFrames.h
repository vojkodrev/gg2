#pragma once
#include <cstdint>
#include "../../../structs/core/Animation.h"
#include "ScaleAnchor.h"

template<int N>
inline void scaleAnimationFrames(
    Animation<N> &animation,
    const float scale[N],
    uint32_t i)
{
    for (int f = 0; f < animation.frameCount[i]; f++)
    {
        scaleAnchor(animation.frame.anchor, scale[i], i, f);
        scaleAnchor(animation.frame.collision, scale[i], i, f);
    }
}
