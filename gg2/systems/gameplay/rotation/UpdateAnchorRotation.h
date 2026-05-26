#pragma once
#include "../../../structs/core/Anchor.h"
#include "../../../structs/core/EntityBase.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include <cstdint>

template<int NItems, int NSlots, int N>
inline void updateAnchorRotation(
    Anchor<NItems, NSlots> &anchor,
    EntityBase<N> &entityBase,
    uint32_t i,
    int slot)
{
    const float centerX = entityBase.position.w[i] * 0.5f;
    const float centerY = entityBase.position.h[i] * 0.5f;

    rotateRectCenter(
        anchor.offX[i][slot],
        anchor.offY[i][slot],
        anchor.w[i][slot],
        anchor.h[i][slot],
        centerX,
        centerY,
        entityBase.rotation.rotate[i]);
}
