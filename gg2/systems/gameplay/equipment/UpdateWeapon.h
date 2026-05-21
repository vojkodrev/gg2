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
    SDL_FRect weaponAnchor = anchorOrCollision(weapon, i, wf);

    SDL_FRect parentAnchorWorld = worldAnchorRect(
        parentPosition.x[i],
        parentPosition.y[i],
        parentPosition.w[i],
        parentAnchor,
        parentFlipX);
    SDL_FPoint parentAnchorCenterWorld = entityColCenter(parentAnchorWorld);

    SDL_FRect weaponAnchorLocal = worldAnchorRect(
        0.0f,
        0.0f,
        weaponData.position.w[i],
        weaponAnchor,
        weaponFlipX);
    SDL_FPoint weaponAnchorCenterLocal = entityColCenter(weaponAnchorLocal);

    weaponData.position.x[i] = parentAnchorCenterWorld.x - weaponAnchorCenterLocal.x;
    weaponData.position.y[i] = parentAnchorCenterWorld.y - weaponAnchorCenterLocal.y;
}
