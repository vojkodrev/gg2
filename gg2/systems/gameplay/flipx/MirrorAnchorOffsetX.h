#pragma once
#include "../../../structs/anchors/Anchor.h"
#include <cstdint>

template<int NEntities, int NSlots, int NAnchors>
inline void mirrorAnchorOffsetX(
    Anchor<NEntities, NSlots, NAnchors> &anchor,
    float parentWidth,
    uint32_t entityIndex,
    int frameIndex,
    int anchorIndex)
{
    anchor.offX[entityIndex][frameIndex][anchorIndex] =
        parentWidth -
        anchor.offX[entityIndex][frameIndex][anchorIndex] -
        anchor.w[entityIndex][frameIndex][anchorIndex];
}
