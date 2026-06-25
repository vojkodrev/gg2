#pragma once
#include <SDL3/SDL.h>
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../node/AStarDecode.h"
#include <cmath>

template<uint32_t N>
float astarH(const AStarContext<N>& ctx, uint32_t astarIndex, int node, SDL_FPoint target)
{
    SDL_Point p = astarDecode(ctx, astarIndex, node);
    float dx = target.x - p.x;
    float dy = target.y - p.y;
    return sqrtf(dx * dx + dy * dy);
}
