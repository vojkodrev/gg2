#pragma once
#include <SDL3/SDL.h>
#include "../../../../../structs/gameplay/ai/AStarContext.h"

void astarDecode(const AStarContext& ctx, int node, SDL_Point& p);
