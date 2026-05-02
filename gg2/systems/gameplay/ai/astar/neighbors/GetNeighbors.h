#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../structs/core/Context.h"

int getNeighbors(const AStarContext& astar, const Context& ctx,
                 int node, int npcIndex, int* neighborsOut);
