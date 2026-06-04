#pragma once
#include "../../../structs/core/Anchor.h"
#include <cstdint>

template<int NItems, int NSlots>
inline void scaleAnchorLocation(
    Anchor<NItems, NSlots> &anchor,
    float scale,
    uint32_t i,
    int slot)
{
    anchor.offX[i][slot] = anchor.initialOffX[i][slot] * scale;
    anchor.offY[i][slot] = anchor.initialOffY[i][slot] * scale;
}
