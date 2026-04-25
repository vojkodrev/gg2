#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../structs/collision/SpatialHash.h"
#include "../../../../../structs/core/Context.h"

int getNeighbors(const AStarContext& astar, const SpatialHash& hash, const Context& ctx,
                 int node, int speed, int* neighborsOut);
