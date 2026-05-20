#pragma once
#include <cstdint>
#include "AnimationFrame.h"
#include "AnimationType.h"

template<int N>
struct Animation
{
    AnimationType animationType[N];
    AnimationFrame<N> frame;
    int frameCount[N];
    int frameIndex[N];
    uint64_t animationStartTime[N];
    uint64_t animationStopTime[N];
};
