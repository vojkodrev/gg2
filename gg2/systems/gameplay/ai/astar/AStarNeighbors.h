#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../structs/collision/SpatialHash.h"
#include "../../../../structs/object/Object.h"

int getNeighbors(const AStarContext& astar, const SpatialHash& hash, const Object& object,
                 int node, int* neighborsOut);
