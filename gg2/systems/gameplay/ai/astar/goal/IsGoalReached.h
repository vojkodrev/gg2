#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include <SDL3/SDL.h>

template<uint32_t N>
bool isGoalReached(const AStarContext<N>& astar, uint32_t astarIndex, const SDL_FRect& col, int node);
