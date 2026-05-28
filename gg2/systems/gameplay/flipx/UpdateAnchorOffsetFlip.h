#pragma once
#include "../../../structs/core/Anchor.h"
#include <cstdint>

template<int NItems, int NSlots>
inline void updateAnchorOffsetFlip(Anchor<NItems, NSlots> &anchor, float parentWidth, uint32_t i, int slot)
{
    anchor.offX[i][slot] = parentWidth - anchor.offX[i][slot] - anchor.w[i][slot];
}
