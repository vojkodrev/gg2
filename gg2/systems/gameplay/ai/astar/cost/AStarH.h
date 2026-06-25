#pragma once
#include <SDL3/SDL.h>
#include "../../../../../structs/gameplay/ai/AStarContext.h"

template<uint32_t N>
float astarH(const AStarContext<N>& ctx, uint32_t astarIndex, int node, SDL_FPoint target);
