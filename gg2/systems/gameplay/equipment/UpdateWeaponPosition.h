#pragma once
#include <cstdint>
#include "../../../utils/animation/AnchorOrCollision.h"
#include "../../../structs/equipment/Weapon.h"
#include "../../../structs/core/Animation.h"
#include "../../../structs/core/EntityPosition.h"
#include "../../../utils/collision/EntityColCenter.h"

template<int N>
inline void updateWeaponPosition(
    Weapon<N> &weaponData,
    const Animation<N> &parentAnimation,
    const EntityPosition<N> &parentPosition,
    uint32_t i)
{
    auto &weapon = weaponData.base.animation;
    if (weapon.frameCount[i] == 0)
        return;

    int wf = weapon.frameIndex[i];
    int pf = parentAnimation.frameIndex[i];

    SDL_FRect parentAnchor = anchorOrCollision(parentAnimation, i, pf);
    SDL_FRect weaponAnchor = anchorOrCollision(weapon, i, wf);

    SDL_FRect parentAnchorWorld = {
        parentPosition.x[i] + parentAnchor.x,
        parentPosition.y[i] + parentAnchor.y,
        parentAnchor.w,
        parentAnchor.h};
    SDL_FPoint parentAnchorCenterWorld = entityColCenter(parentAnchorWorld);

    SDL_FPoint weaponAnchorCenterLocal = entityColCenter(weaponAnchor);

    weaponData.base.position.x[i] = parentAnchorCenterWorld.x - weaponAnchorCenterLocal.x;
    weaponData.base.position.y[i] = parentAnchorCenterWorld.y - weaponAnchorCenterLocal.y;
}
