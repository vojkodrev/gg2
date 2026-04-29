#pragma once
#include <SDL3/SDL.h>
#include "../../../../../structs/gameplay/ai/AStarContext.h"

float astarH(const AStarContext& ctx, int node, SDL_FPoint target);
