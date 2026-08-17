#pragma once
#include "Anchor.h"
#include "AnchorPoint.h"

template<int NEntities, int NSlots>
struct CenteredAnchor
{
    Anchor<NEntities, NSlots, 1> anchor;
    AnchorPoint<NEntities, NSlots> center;
};
