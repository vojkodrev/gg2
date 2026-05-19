#pragma once
#include "Weapon.h"

template<int N>
struct Equipment
{
    Weapon<N> weapon;
};
