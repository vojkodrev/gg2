#pragma once
#include <cstdint>
#include "Animation.h"

template<int N>
void advanceAnimation(
    Animation<N> &anim,
    uint32_t i,
    uint64_t now)
{
    int fc = anim.frameCount[i];
    if (fc <= 1)
        return;

    uint64_t cycleDuration = anim.cycleDuration[i];
    if (cycleDuration == 0)
        return;

    uint64_t elapsed = (now - anim.animationStartTime[i]) % cycleDuration;

    uint64_t accumulated = 0;
    for (int f = 0; f < fc; f++)
    {
        accumulated += anim.frame.frameDuration[i][f];
        if (elapsed < accumulated)
        {
            anim.frameIndex[i] = f;
            break;
        }
        if (f == fc - 1)
            anim.frameIndex[i] = f;
    }
}
