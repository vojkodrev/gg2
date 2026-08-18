#pragma once
#include "../../../utils/rect/AlignEntityToParentAnchor.h"

template<int N>
inline void alignAmmoToWeaponAnchor(
    EntityBase<N> &ammoBase,
    Anchor<N, MAX_ANIMATION_FRAMES, 1> &weaponAmmoAnchor,
    const EntityBase<N> &weaponBase,
    const EntityBase<N> &parentBase,
    uint32_t entityIndex)
{
    const int frameIndex = weaponBase.animation.frameIndex[entityIndex];
    SDL_FRect anchor = {
        weaponAmmoAnchor.offX[entityIndex][frameIndex][0],
        weaponAmmoAnchor.offY[entityIndex][frameIndex][0],
        weaponAmmoAnchor.w[entityIndex][frameIndex][0],
        weaponAmmoAnchor.h[entityIndex][frameIndex][0]};

    if (anchor.w > 0.0f && anchor.h > 0.0f)
        alignEntityToParentAnchor(
            ammoBase,
            anchor,
            weaponBase.position,
            entityIndex);
    else
        alignEntityToParentAnchor(
            ammoBase,
            parentBase.animation,
            parentBase.position,
            entityIndex);
}
