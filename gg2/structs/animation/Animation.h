#pragma once
#include <cstdint>
#include "AnimationFrame.h"
#include "AnimationState.h"
#include "AnimationStop.h"
#include "AnimationType.h"

template<int N>
struct Animation
{
    AnimationType animationType[N];
    AnimationState animationState[N];
    AnimationStop animationStop[N];
    uint64_t animationStartTime[N];
    uint64_t cycleDuration[N];

    AnimationFrame<N> frame;
    int frameCount[N];
    int frameIndex[N];

    float rotationStartAngle[N];
    float rotationStopAngle[N];
    float rotate[N];
};
