#pragma once
#include "../../../utils/rect/AlignEntityToParentAnchor.h"

template<int N>
inline void alignAmmoToWeaponAnchor(
    EntityBase<N> &ammoBase,
    Anchor<N, MAX_ANIMATION_FRAMES> &weaponAmmoAnchor,
    const EntityBase<N> &weaponBase,
    const EntityBase<N> &parentBase,
    uint32_t i)
{
    const int frameIndex = weaponBase.animation.frameIndex[i];
    SDL_FRect anchor = {
        weaponAmmoAnchor.offX[i][frameIndex],
        weaponAmmoAnchor.offY[i][frameIndex],
        weaponAmmoAnchor.w[i][frameIndex],
        weaponAmmoAnchor.h[i][frameIndex]};

    if (anchor.w > 0.0f && anchor.h > 0.0f)
        alignEntityToParentAnchor(
            ammoBase,
            anchor,
            weaponBase.position,
            i);
    else
        alignEntityToParentAnchor(
            ammoBase,
            parentBase.animation,
            parentBase.position,
            i);
}
