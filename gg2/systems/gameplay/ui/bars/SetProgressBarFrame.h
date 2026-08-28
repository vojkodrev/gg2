#pragma once
#include <algorithm>
#include <cstdint>

template<typename TBar, typename TValue>
inline void setProgressBarFrame(
    TBar &bar,
    TValue currentValue,
    TValue maxValue,
    uint32_t index)
{
    const int frameCount = bar.base.animation.frameCount[index];
    const TValue value = std::clamp(currentValue, TValue{}, maxValue);

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
