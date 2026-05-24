#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityAnchorAABB(const Player &p, float buffer = 0.0f)
{
    int f = p.animation.frameIndex[0];
    return {
        p.position.x[0] + p.animation.frame.anchor.offX[0][f] - buffer,
        p.position.y[0] + p.animation.frame.anchor.offY[0][f] - buffer,
        p.animation.frame.anchor.w[0][f] + buffer * 2,
        p.animation.frame.anchor.h[0][f] + buffer * 2
    };
}
