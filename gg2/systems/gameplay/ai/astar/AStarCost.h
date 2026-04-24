#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"

float astarH(const AStarContext& ctx, int node, float tx, float ty);
float astarD(int fromNode, int toNode, int speed);
