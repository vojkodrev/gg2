#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"

bool closedContains(const AStarClosedSet& cs, int node, int generation);
