#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../structs/core/Context.h"

template<uint32_t N>
int getNeighbors(
    const AStarContext<N>& astar,
    uint32_t astarIndex,
    const Context& ctx,
    int node,
    int npcIndex,
    int* neighborsOut);
