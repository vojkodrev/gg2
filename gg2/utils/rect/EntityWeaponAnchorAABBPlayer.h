#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityWeaponAnchorAABB(const Player &p, float buffer = 0.0f)
{
    const auto &weapon = p.equipment.weapon;
    if (weapon.animation.frameCount[0] == 0)
        return {0, 0, 0, 0};

    int f = weapon.animation.frameIndex[0];
    return {
        weapon.position.x[0] + weapon.animation.frame.anchor.offX[0][f] - buffer,
        weapon.position.y[0] + weapon.animation.frame.anchor.offY[0][f] - buffer,
        weapon.animation.frame.anchor.w[0][f] + buffer * 2,
        weapon.animation.frame.anchor.h[0][f] + buffer * 2
    };
}
