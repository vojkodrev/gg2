#pragma once
#include <cstdlib>

static constexpr float IDLE_TIME_MIN = 1.0f;
static constexpr float IDLE_TIME_MAX = 3.0f;

inline float RandomIdleTimer()
{
    return IDLE_TIME_MIN + (float)rand() / RAND_MAX * (IDLE_TIME_MAX - IDLE_TIME_MIN);
}
