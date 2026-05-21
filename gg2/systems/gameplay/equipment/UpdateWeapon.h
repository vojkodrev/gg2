#pragma once
#include <cstdint>
#include "AnchorOrCollision.h"
#include "WorldAnchorRect.h"
#include "../../../structs/equipment/Weapon.h"
#include "../../../structs/core/Animation.h"
#include "../../../structs/core/EntityPosition.h"
#include "../../../structs/core/Facing.h"
#include "../../../utils/collision/EntityColCenter.h"

template<int N>
inline void updateWeapon(
    Weapon<N> &weaponData,
    const Animation<N> &parentAnimation,
    const EntityPosition<N> &parentPosition,
    const Facing<N> &parentFacing,
    uint32_t i)
{
    auto &weapon = weaponData.animation;
    if (weapon.frameCount[i] == 0)
        return;

    int wf = weapon.frameIndex[i];
    int pf = parentAnimation.frameIndex[i];

    bool parentFlipX = parentFacing.flipX[i];
    bool weaponFlipX = weaponData.facing.flipX[i];

    SDL_FRect parentAnchor = anchorOrCollision(parentAnimation, i, pf);
    SDL_FRect parentAnchorWorld = worldAnchorRect(
        parentPosition.x[i],
        parentPosition.y[i],
        parentPosition.w[i],
        parentAnchor,
        parentFlipX);

    SDL_FRect weaponAnchor = anchorOrCollision(weapon, i, wf);
    SDL_FRect weaponAnchorWorld = worldAnchorRect(
        0.0f,
        0.0f,
        weaponData.position.w[i],
        weaponAnchor,
        weaponFlipX);

    SDL_FPoint parentCenter = entityColCenter(parentAnchorWorld);
    SDL_FPoint weaponCenter = entityColCenter(weaponAnchorWorld);
    weaponData.position.x[i] = parentCenter.x - weaponCenter.x;
    weaponData.position.y[i] = parentCenter.y - weaponCenter.y;
}
