#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include <SDL3/SDL.h>

bool isGoalReached(const AStarContext& astar, const SDL_FRect& col, int node);
