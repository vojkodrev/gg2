#pragma once
#include <algorithm>
#include <cstdint>

template<typename TBar>
inline void setProgressBarFrame(
    TBar &bar,
    int currentValue,
    int maxValue,
    uint32_t index)
{
    const int frameCount = bar.base.animation.frameCount[index];
    const int value = std::clamp(currentValue, 0, maxValue);

    if (frameCount <= 0)
        return;

    if (maxValue <= 0)
    {
        bar.base.animation.frameIndex[index] = 0;
        return;
    }

    bar.base.animation.frameIndex[index] =
        value * (frameCount - 1) / maxValue;
}
