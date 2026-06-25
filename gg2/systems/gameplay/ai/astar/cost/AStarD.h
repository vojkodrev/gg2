#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"

template<uint32_t N>
float astarD(const AStarContext<N>& ctx, uint32_t astarIndex, int fromNode, int toNode);
