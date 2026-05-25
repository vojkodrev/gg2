#pragma once
#include <cstdint>

template<typename PositionData, int N>
inline void scaleEquipmentSize(PositionData &position, const float (&scale)[N], uint32_t i)
{
    position.w[i] = position.initialW[i] * scale[i];
    position.h[i] = position.initialH[i] * scale[i];
}
