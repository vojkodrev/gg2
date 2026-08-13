#pragma once

template<int NItems, int NSlots>
struct AnchorPoint
{
    float x[NItems][NSlots];
    float y[NItems][NSlots];
};
