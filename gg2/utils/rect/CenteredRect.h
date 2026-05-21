#pragma once
#include <SDL3/SDL.h>

inline SDL_FRect centeredRect(SDL_FPoint center, float w, float h, float buffer = 0.0f)
{
    float bw = w + buffer * 2;
    float bh = h + buffer * 2;
    return { center.x - bw * 0.5f, center.y - bh * 0.5f, bw, bh };
}
