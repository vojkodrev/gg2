#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityColAABB(const Player &p, float buffer = 0.0f)
{
    int f = p.animation.frameIndex[0];
    return {p.position.x[0] + p.animation.frame.collision.offX[0][f] - buffer, p.position.y[0] + p.animation.frame.collision.offY[0][f] - buffer,
            p.animation.frame.collision.w[0][f] + buffer * 2, p.animation.frame.collision.h[0][f] + buffer * 2};
}
