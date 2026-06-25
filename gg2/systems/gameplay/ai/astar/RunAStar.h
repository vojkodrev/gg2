#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../structs/core/Context.h"
#include <SDL3/SDL.h>

// Returns path length, or -1 if no path found. Path nodes written to pathOut.
template<uint32_t N>
int runAStar(
    AStarContext<N>& astar,
    uint32_t astarIndex,
    Context& ctx,
    int npcIndex,
    const SDL_FRect& destCol,
    int* pathOut);
