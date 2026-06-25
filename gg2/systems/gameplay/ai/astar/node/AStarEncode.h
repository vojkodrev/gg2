#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include <SDL3/SDL.h>

template<uint32_t N>
int astarEncode(const AStarContext<N>& ctx, uint32_t astarIndex, SDL_Point p);
