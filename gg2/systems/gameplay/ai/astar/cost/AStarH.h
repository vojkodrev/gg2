#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"

float astarH(const AStarContext& ctx, int node, SDL_FPoint target);
