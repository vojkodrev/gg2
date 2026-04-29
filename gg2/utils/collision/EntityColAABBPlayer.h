#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

inline SDL_FRect entityColAABB(const Player &p, float buffer = 0.0f)
{
    return {p.x + p.colOffX - buffer, p.y + p.colOffY - buffer,
            p.colW + buffer * 2, p.colH + buffer * 2};
}
