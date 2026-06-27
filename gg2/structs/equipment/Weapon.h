#pragma once
#include "../core/Anchor.h"
#include "../core/EntityBase.h"
#include "WeaponType.h"

template<int N>
struct Weapon
{
    EntityBase<N> base;
    Anchor<N, 1> ammoAnchor;
    WeaponType type[N] = {};
    bool showAmmo[N] = {};
};
