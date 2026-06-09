#pragma once
#include "../core/Anchor.h"
#include "../core/EntityBase.h"

template<int N>
struct Weapon
{
    EntityBase<N> base;
    Anchor<N, 1> ammoAnchor;
    bool hasAmmo[N] = {};
    bool showAmmo[N] = {};
};
