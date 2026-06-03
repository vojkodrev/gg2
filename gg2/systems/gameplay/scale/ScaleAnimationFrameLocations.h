#pragma once
#include <cstdint>
#include "../../../structs/core/Animation.h"
#include "ScaleAnchorLocation.h"

template<int N>
inline void scaleAnimationFrameLocations(
    Animation<N> &animation,
    const float scale[N],
    uint32_t i)
{
    for (int f = 0; f < animation.frameCount[i]; f++)
    {
        scaleAnchorLocation(animation.frame.anchor, scale[i], i, f);
        scaleAnchorLocation(animation.frame.collision, scale[i], i, f);
    }
}
