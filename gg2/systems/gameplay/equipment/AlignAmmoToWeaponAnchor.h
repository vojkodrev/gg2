#pragma once
#include "AlignEquipmentToParentAnchor.h"

template<int N>
inline void alignAmmoToWeaponAnchor(
    EntityBase<N> &ammoBase,
    Anchor<N, 1> &weaponAmmoAnchor,
    const EntityBase<N> &weaponBase,
    const EntityBase<N> &parentBase,
    uint32_t i)
{
    SDL_FRect anchor = {
        weaponAmmoAnchor.offX[i][0],
        weaponAmmoAnchor.offY[i][0],
        weaponAmmoAnchor.w[i][0],
        weaponAmmoAnchor.h[i][0]};

    if (anchor.w > 0.0f && anchor.h > 0.0f)
        alignEquipmentToParentAnchor(
            ammoBase,
            anchor,
            weaponBase.position,
            i);
    else
        alignEquipmentToParentAnchor(
            ammoBase,
            parentBase.animation,
            parentBase.position,
            i);
}
