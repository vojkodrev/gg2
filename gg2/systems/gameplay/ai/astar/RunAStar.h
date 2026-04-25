#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../structs/core/Context.h"
#include <SDL3/SDL.h>

// Returns true if a path was found. Path is stored in astar.path / astar.pathLen.
bool runAStar(AStarContext& astar, Context& ctx,
              int startNode, float goalX, float goalY, const SDL_FRect& col, int speed);
