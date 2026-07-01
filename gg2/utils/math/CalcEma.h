#pragma once
#include <SDL3/SDL.h>

static constexpr float EMA_WINDOW = 20.0f;

inline void calcEma(const Uint64 &time, float &avgTime)
{
    const float sample = static_cast<float>(time);
    if (avgTime == 0.0f)
        avgTime = sample;
    else
        avgTime += (sample - avgTime) / EMA_WINDOW;
}
