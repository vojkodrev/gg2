#pragma once
#include <SDL3/SDL.h>

inline int encodeGridIndex(SDL_Point p, int width)
{
    return p.y * width + p.x;
}
