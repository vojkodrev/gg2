#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../structs/core/Context.h"
#include <SDL3/SDL.h>

// Returns path length, or -1 if no path found. Path nodes written to pathOut.
int runAStar(AStarContext& astar, Context& ctx,
             int npcIndex, const SDL_FRect& destCol,
             int* pathOut);
