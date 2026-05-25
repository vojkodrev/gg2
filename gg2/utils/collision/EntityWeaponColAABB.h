#pragma once
#include <SDL3/SDL.h>
#include "../../structs/equipment/Weapon.h"

template<int N>
inline SDL_FRect entityWeaponColAABB(const Weapon<N> &weapon, uint32_t i, float buffer = 0.0f)
{
    if (weapon.base.animation.frameCount[i] == 0)
        return {0, 0, 0, 0};

    int f = weapon.base.animation.frameIndex[i];
    return {
        weapon.base.position.x[i] + weapon.base.animation.frame.collision.offX[i][f] - buffer,
        weapon.base.position.y[i] + weapon.base.animation.frame.collision.offY[i][f] - buffer,
        weapon.base.animation.frame.collision.w[i][f] + buffer * 2,
        weapon.base.animation.frame.collision.h[i][f] + buffer * 2
    };
}
