#pragma once

template<int NEntities, int NSlots>
struct AnchorPoint
{
    float x[NEntities][NSlots];
    float y[NEntities][NSlots];
};
