#pragma once
#include <SDL3/SDL.h>
#include "../../structs/equipment/Weapon.h"

template<int N>
inline SDL_FRect entityWeaponColAABB(const Weapon<N> &weapon, uint32_t i, float buffer = 0.0f)
{
    if (weapon.animation.frameCount[i] == 0)
        return {0, 0, 0, 0};

    int f = weapon.animation.frameIndex[i];
    return {
        weapon.position.x[i] + weapon.animation.frame.collision.offX[i][f] - buffer,
        weapon.position.y[i] + weapon.animation.frame.collision.offY[i][f] - buffer,
        weapon.animation.frame.collision.w[i][f] + buffer * 2,
        weapon.animation.frame.collision.h[i][f] + buffer * 2
    };
}
