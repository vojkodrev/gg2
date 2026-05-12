#pragma once
#include <SDL3/SDL.h>

inline SDL_Point decodeGridIndex(int index, int width)
{
    return { index % width, index / width };
}
