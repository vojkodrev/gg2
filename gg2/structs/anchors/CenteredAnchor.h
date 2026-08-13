#pragma once
#include "Anchor.h"
#include "AnchorPoint.h"

template<int NItems, int NSlots>
struct CenteredAnchor
{
    Anchor<NItems, NSlots> anchor;
    AnchorPoint<NItems, NSlots> center;
};
