#pragma once
#include <cstdint>

template<int NItems, int NSlots>
struct SpriteSrc
{
    uint32_t x[NItems][NSlots];
    uint32_t y[NItems][NSlots];
    uint32_t w[NItems][NSlots];
    uint32_t h[NItems][NSlots];
    float rotate[NItems][NSlots];
    float initialAngle[NItems][NSlots];
};
