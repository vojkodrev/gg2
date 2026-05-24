#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityWeaponColAABB(const Player &p, float buffer = 0.0f)
{
    const auto &weapon = p.equipment.weapon;
    if (weapon.animation.frameCount[0] == 0)
        return {0, 0, 0, 0};

    int f = weapon.animation.frameIndex[0];
    return {
        weapon.position.x[0] + weapon.animation.frame.collision.offX[0][f] - buffer,
        weapon.position.y[0] + weapon.animation.frame.collision.offY[0][f] - buffer,
        weapon.animation.frame.collision.w[0][f] + buffer * 2,
        weapon.animation.frame.collision.h[0][f] + buffer * 2
    };
}
