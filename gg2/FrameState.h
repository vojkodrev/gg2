#pragma once
#include <cstdint>
#include <SDL3/SDL.h>

struct FrameState
{
    uint32_t maxFps;
    uint32_t frameCount;
    Uint64 lastTicks;
    Uint64 now;
    float dt;
    Uint64 frameTime;
    Uint64 targetTime;
};
