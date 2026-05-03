#pragma once
#include <cstdint>
#include "AnimationFrame.h"

template<int N>
struct Animation
{
    AnimationFrame<N> frame;
    int frameCount[N];
    int frameIndex[N];
    uint64_t animationStartTime[N];
};
