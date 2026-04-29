#pragma once
#include <SDL3/SDL.h>

inline SDL_FRect centeredRect(float cx, float cy, float w, float h)
{
    return { cx - w * 0.5f, cy - h * 0.5f, w, h };
}
