#pragma once

template<int NItems, int NSlots>
struct Anchor
{
    bool exists[NItems][NSlots] = {};
    float initialOffX[NItems][NSlots];
    float initialOffY[NItems][NSlots];
    float initialW[NItems][NSlots];
    float initialH[NItems][NSlots];
    float offX[NItems][NSlots];
    float offY[NItems][NSlots];
    float w[NItems][NSlots];
    float h[NItems][NSlots];
};
