#pragma once
#include "../anchors/Anchor.h"
#include "../core/constants/AnimationConstants.h"

template<int N>
struct RangedWeapon
{
    Anchor<N, MAX_ANIMATION_FRAMES, 1> ammoAnchor;
    bool showAmmo[N] = {};
};
