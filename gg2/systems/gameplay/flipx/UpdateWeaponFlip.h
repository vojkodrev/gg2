#pragma once
#include "../../../structs/core/Facing.h"
#include <cstdint>

template<int N>
inline void updateWeaponFlip(const Facing<N> &parentFacing, Facing<N> &weaponFacing, uint32_t i)
{
    bool parentNeedsFlip = parentFacing.facing[i] != weaponFacing.initialFacing[i];
    bool weaponFacingChanged = weaponFacing.facing[i] != weaponFacing.initialFacing[i];
    weaponFacing.flipX[i] = parentNeedsFlip != weaponFacingChanged;
}
