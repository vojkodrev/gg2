#pragma once
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateWeaponFlip.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void updateWeaponAnchorCollisionFlip(
    const Facing<N> &parentFacing,
    EntityBase<N> &weaponBase,
    uint32_t i)
{
    updateWeaponFlip(parentFacing, weaponBase.facing, i);
    updateEntityAnchorAndCollisionFlip(weaponBase, i);
}
