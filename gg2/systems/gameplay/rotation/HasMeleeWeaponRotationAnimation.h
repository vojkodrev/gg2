#pragma once
#include "../../../structs/equipment/Weapon.h"
#include <cstdint>

template<int N>
inline bool hasMeleeWeaponRotationAnimation(const Weapon<N> &weapon, uint32_t i)
{
    return
        weapon.type[i] == WeaponType::Melee &&
        weapon.base.animation.animationType[i] == AnimationType::Rotation;
}
