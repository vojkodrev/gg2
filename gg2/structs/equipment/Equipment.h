#pragma once
#include "Ammo.h"
#include "Weapon.h"

template<int N>
struct Equipment
{
    Ammo<N> ammo;
    Weapon<N> weapon;
};
