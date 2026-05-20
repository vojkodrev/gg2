#pragma once

template<int NItems, int NSlots>
struct Anchor
{
    float offX[NItems][NSlots];
    float offY[NItems][NSlots];
    float w[NItems][NSlots];
    float h[NItems][NSlots];
};
