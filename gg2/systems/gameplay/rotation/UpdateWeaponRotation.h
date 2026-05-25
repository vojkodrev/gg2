#pragma once
#include "UpdateEntityAnchorAndCollisionRotation.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void updateWeaponRotation(EntityBase<N> &weaponBase, uint32_t i)
{
    if (weaponBase.animation.frameCount[i] == 0)
        return;

    weaponBase.rotation.rotate[i] = weaponBase.facing.flipX[i]
        ? -weaponBase.rotation.initialRotate[i]
        : weaponBase.rotation.initialRotate[i];

    updateEntityAnchorAndCollisionRotation(
        weaponBase.animation,
        i,
        weaponBase.position.w[i],
        weaponBase.position.h[i],
        weaponBase.rotation.rotate[i]);
}
