#pragma once
#include "../core/Anchor.h"
#include "../core/AnchorPoint.h"
#include "../core/EntityBase.h"
#include "WeaponType.h"

template<int N>
struct Weapon
{
    EntityBase<N> base;
    Anchor<N, MAX_ANIMATION_FRAMES> ammoAnchor;
    Anchor<N, MAX_ANIMATION_FRAMES> entityRangedCollision;
    AnchorPoint<N, MAX_ANIMATION_FRAMES> entityRangedCollisionCenter;
    WeaponType type[N] = {};
    bool showAmmo[N] = {};
};
