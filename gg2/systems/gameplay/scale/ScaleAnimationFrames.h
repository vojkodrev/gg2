#pragma once
#include <cstdint>
#include "../../../structs/core/Animation.h"
#include "ScaleAnchorLocation.h"
#include "ScaleAnchorSize.h"

template<int N>
inline void scaleAnimationFrames(
    Animation<N> &animation,
    const float scale[N],
    uint32_t i)
{
    for (int f = 0; f < animation.frameCount[i]; f++)
    {
        scaleAnchorLocation(animation.frame.anchor, scale[i], i, f);
        scaleAnchorSize(animation.frame.anchor, scale[i], i, f);
        scaleAnchorLocation(animation.frame.collision, scale[i], i, f);
        scaleAnchorSize(animation.frame.collision, scale[i], i, f);
    }
}
