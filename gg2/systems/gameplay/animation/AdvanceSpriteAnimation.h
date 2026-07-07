#pragma once
#include <cstdint>
#include "Animation.h"

template<int N>
void advanceSpriteAnimation(
    Animation<N> &anim,
    uint32_t i,
    uint64_t now)
{
    anim.animationState[i] = AnimationState::Running;

    int fc = anim.frameCount[i];
    if (fc <= 1)
        return;

    uint64_t cycleDuration = anim.cycleDuration[i];
    if (cycleDuration == 0)
        return;

    uint64_t elapsed = (now - anim.animationStartTime[i]) % cycleDuration;
    int frameIndex = 0;
    uint64_t accumulated = anim.frame.frameDuration[i][frameIndex];

    while (frameIndex + 1 < fc && elapsed >= accumulated)
    {
        frameIndex++;
        accumulated += anim.frame.frameDuration[i][frameIndex];
    }

    anim.frameIndex[i] = frameIndex;
}
