#pragma once
#include "../core/Anchor.h"
#include "../core/AnchorPoint.h"
#include "../core/constants/AnimationConstants.h"

template<int N>
struct RangedWeapon
{
    Anchor<N, MAX_ANIMATION_FRAMES> ammoAnchor;
    Anchor<N, MAX_ANIMATION_FRAMES> entityCollision;
    AnchorPoint<N, MAX_ANIMATION_FRAMES> entityCollisionCenter;
    bool showAmmo[N] = {};
};
