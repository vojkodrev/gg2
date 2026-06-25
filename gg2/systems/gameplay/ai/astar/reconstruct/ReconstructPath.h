#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include <SDL3/SDL.h>

template<uint32_t N>
int reconstructPath(
    AStarContext<N>& ctx,
    uint32_t astarIndex,
    int current,
    SDL_FPoint goalCenter,
    int* path);
