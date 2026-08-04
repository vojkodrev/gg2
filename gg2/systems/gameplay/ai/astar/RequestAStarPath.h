#pragma once
#include "../../../../structs/core/Context.h"
#include <SDL3/SDL.h>

void requestAStarPath(
    Context& ctx, int npcIndex,
    const SDL_FRect& moverBox,
    const SDL_FPoint& moverCenter,
    const SDL_FRect& destCol,
    int targetNpcIndex,
    bool isPlayerBlocking);
