#pragma once
#include <SDL3/SDL.h>
#include "../../../../../structs/gameplay/ai/AStarContext.h"

template<uint32_t N>
SDL_Point astarDecode(const AStarContext<N>& ctx, uint32_t astarIndex, int node);
