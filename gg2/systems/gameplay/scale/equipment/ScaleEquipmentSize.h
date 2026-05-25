#pragma once
#include <cstdint>

template<typename PositionData, typename FrameCountT, int N>
inline void scaleEquipmentSize(PositionData &position, const float (&scale)[N], const FrameCountT (&frameCount)[N], uint32_t i)
{
    if (frameCount[i] == 0)
        return;

    position.w[i] = position.initialW[i] * scale[i];
    position.h[i] = position.initialH[i] * scale[i];
}
