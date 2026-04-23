#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"

void closedInsert(AStarClosedSet& cs, int node, int generation);
bool closedContains(const AStarClosedSet& cs, int node, int generation);
