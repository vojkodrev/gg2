#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../structs/core/Context.h"

bool isBlocked(const AStarContext& astar, const Context& ctx, SDL_Point node, SDL_FRect startCol);
