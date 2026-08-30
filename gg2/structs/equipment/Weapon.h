#pragma once
#include "../entity/EntityBase.h"
#include "MagicWeapon.h"
#include "RangedWeapon.h"
#include "WeaponType.h"

template<int N>
struct Weapon
{
    EntityBase<N> base;
    WeaponType type[N] = {};
    bool exists[N] = {};
    
    MagicWeapon<N> magic;
    RangedWeapon<N> ranged;
    
    int zIndex[N] = {};
};
