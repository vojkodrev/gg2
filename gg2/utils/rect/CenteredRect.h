#pragma once
#include <SDL3/SDL.h>

inline SDL_FRect centeredRect(
    SDL_FPoint center,
    const SDL_FRect &rect,
    SDL_FPoint customCenter,
    float buffer = 0.0f)
{
    return {
        center.x - (customCenter.x - rect.x) - buffer,
        center.y - (customCenter.y - rect.y) - buffer,
        rect.w + buffer * 2.0f,
        rect.h + buffer * 2.0f
    };
}

inline SDL_FRect centeredRect(SDL_FPoint center, float w, float h, float buffer = 0.0f)
{
    const SDL_FRect rect = {0.0f, 0.0f, w, h};
    return centeredRect(center, rect, {w * 0.5f, h * 0.5f}, buffer);
}
