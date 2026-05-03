#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityColAABB(const Player &p, float buffer = 0.0f)
{
    return {p.position.x[0] + p.collision.offX[0] - buffer, p.position.y[0] + p.collision.offY[0] - buffer,
            p.collision.w[0] + buffer * 2, p.collision.h[0] + buffer * 2};
}
