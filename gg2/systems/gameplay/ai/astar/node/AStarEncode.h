#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include <SDL3/SDL.h>

int astarEncode(const AStarContext& ctx, SDL_Point p);
