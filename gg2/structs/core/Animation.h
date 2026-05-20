#pragma once
#include <cstdint>
#include "AnimationFrame.h"
#include "AnimationType.h"

template<int N>
struct Animation
{
    AnimationFrame<N> frame;
    AnimationType animationType[N];
    int frameCount[N];
    int frameIndex[N];
    uint64_t animationStartTime[N];
    uint64_t animationStopTime[N];
};
