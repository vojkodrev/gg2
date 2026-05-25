#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityAnchorAABB(const Player &p, float buffer = 0.0f)
{
    int f = p.base.animation.frameIndex[0];
    return {
        p.base.position.x[0] + p.base.animation.frame.anchor.offX[0][f] - buffer,
        p.base.position.y[0] + p.base.animation.frame.anchor.offY[0][f] - buffer,
        p.base.animation.frame.anchor.w[0][f] + buffer * 2,
        p.base.animation.frame.anchor.h[0][f] + buffer * 2
    };
}
