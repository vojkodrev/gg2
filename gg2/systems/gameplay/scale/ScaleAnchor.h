#pragma once
#include "../../../structs/core/Anchor.h"
#include <cstdint>

template<int NItems, int NSlots>
inline void scaleAnchor(
    Anchor<NItems, NSlots> &anchor,
    float scale,
    uint32_t i,
    int slot)
{
    anchor.offX[i][slot] = anchor.initialOffX[i][slot] * scale;
    anchor.offY[i][slot] = anchor.initialOffY[i][slot] * scale;
    anchor.w[i][slot] = anchor.initialW[i][slot] * scale;
    anchor.h[i][slot] = anchor.initialH[i][slot] * scale;
}
