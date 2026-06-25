#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../structs/core/Context.h"

template<uint32_t N>
bool isBlocked(const AStarContext<N>& astar, uint32_t astarIndex, const Context& ctx, SDL_Point node, int npcIndex);
