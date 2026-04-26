#pragma once
#include "../../../../structs/core/Context.h"
#include <SDL3/SDL.h>

void requestAStarPath(Context& ctx, int npcIndex,
                      SDL_FPoint start, const SDL_FRect& destCol, int speed);
