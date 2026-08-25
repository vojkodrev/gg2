#pragma once
#include "../entity/EntityBase.h"
#include "RangedWeapon.h"
#include "WeaponType.h"

template<int N>
struct Weapon
{
    int zIndex[N] = {};
    EntityBase<N> base;
    RangedWeapon<N> ranged;
    WeaponType type[N] = {};
    bool exists[N] = {};
};
