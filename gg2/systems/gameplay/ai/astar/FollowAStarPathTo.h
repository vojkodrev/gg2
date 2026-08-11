#pragma once
#include "../../../../structs/core/Context.h"
#include <SDL3/SDL.h>

bool followAStarPathTo(
    uint32_t n,
    Context &ctx,
    SDL_FRect targetCol,
    int targetNpcIndex);
