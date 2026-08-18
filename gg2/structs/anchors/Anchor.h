#pragma once

template<int NEntities, int NSlots, int NAnchors>
struct Anchor
{
    bool exists[NEntities][NSlots][NAnchors] = {};
    float initialOffX[NEntities][NSlots][NAnchors];
    float initialOffY[NEntities][NSlots][NAnchors];
    float initialW[NEntities][NSlots][NAnchors];
    float initialH[NEntities][NSlots][NAnchors];
    float offX[NEntities][NSlots][NAnchors];
    float offY[NEntities][NSlots][NAnchors];
    float w[NEntities][NSlots][NAnchors];
    float h[NEntities][NSlots][NAnchors];
};
