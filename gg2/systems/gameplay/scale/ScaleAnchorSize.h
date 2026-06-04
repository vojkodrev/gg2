#pragma once
#include "../../../structs/core/Anchor.h"
#include <cstdint>

template<int NItems, int NSlots>
inline void scaleAnchorSize(
    Anchor<NItems, NSlots> &anchor,
    float scale,
    uint32_t i,
    int slot)
{
    anchor.w[i][slot] = anchor.initialW[i][slot] * scale;
    anchor.h[i][slot] = anchor.initialH[i][slot] * scale;
}
