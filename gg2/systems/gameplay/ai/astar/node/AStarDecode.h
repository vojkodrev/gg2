#pragma once
#include <SDL3/SDL.h>
#include "../../../../../structs/gameplay/ai/AStarContext.h"

SDL_Point astarDecode(const AStarContext& ctx, int node);
