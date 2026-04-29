#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include <SDL3/SDL.h>

int reconstructPath(AStarContext& ctx, int current, SDL_FPoint goalCenter, int* path);
