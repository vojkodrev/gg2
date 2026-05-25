#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityColAABB(const Player &p, float buffer = 0.0f)
{
    int f = p.base.animation.frameIndex[0];
    return {p.base.position.x[0] + p.base.animation.frame.collision.offX[0][f] - buffer, p.base.position.y[0] + p.base.animation.frame.collision.offY[0][f] - buffer,
            p.base.animation.frame.collision.w[0][f] + buffer * 2, p.base.animation.frame.collision.h[0][f] + buffer * 2};
}
