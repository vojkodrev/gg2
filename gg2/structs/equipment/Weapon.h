#pragma once
#include "../core/Anchor.h"
#include "../core/EntityBase.h"
#include "WeaponType.h"

template<int N>
struct Weapon
{
    EntityBase<N> base;
    Anchor<N, MAX_ANIMATION_FRAMES> ammoAnchor;
    WeaponType type[N] = {};
    bool showAmmo[N] = {};
};
