#pragma once
#include "../../../structs/anchors/Anchor.h"
#include <cstdint>

template<int NEntities, int NSlots, int NAnchors>
inline void scaleAnchorLocation(
    Anchor<NEntities, NSlots, NAnchors> &anchor,
    float scale,
    uint32_t entityIndex,
    int frameIndex,
    int anchorIndex)
{
    anchor.offX[entityIndex][frameIndex][anchorIndex] =
        anchor.initialOffX[entityIndex][frameIndex][anchorIndex] * scale;
    anchor.offY[entityIndex][frameIndex][anchorIndex] =
        anchor.initialOffY[entityIndex][frameIndex][anchorIndex] * scale;
}
