#pragma once
#include "Context.h"
#include <cstdint>

void moveNpcColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed);

void moveNpcColCenterToward(
    Context &ctx,
    uint32_t n,
    const SDL_FPoint &colCenter,
    SDL_FPoint target,
    float speed);
