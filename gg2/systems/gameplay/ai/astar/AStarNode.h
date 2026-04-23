#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"

int   astarEncode(const AStarContext& ctx, int x, int y);
void  astarDecode(const AStarContext& ctx, int node, int& x, int& y);
