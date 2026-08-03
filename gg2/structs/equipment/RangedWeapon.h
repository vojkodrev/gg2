#pragma once
#include "../core/Anchor.h"
#include "../core/constants/AnimationConstants.h"

template<int N>
struct RangedWeapon
{
    Anchor<N, MAX_ANIMATION_FRAMES> ammoAnchor;
    bool showAmmo[N] = {};
};
