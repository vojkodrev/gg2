#pragma once
#include <SDL3/SDL.h>

inline SDL_FRect centeredRect(SDL_FPoint center, float w, float h)
{
    return { center.x - w * 0.5f, center.y - h * 0.5f, w, h };
}
