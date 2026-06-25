#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../node/AStarDecode.h"
#include <SDL3/SDL.h>

template<uint32_t N>
bool isGoalReached(const AStarContext<N>& astar, uint32_t astarIndex, const SDL_FRect& col, int node)
{
    SDL_Point p = astarDecode(astar, astarIndex, node);
    SDL_FPoint fp = { (float)p.x, (float)p.y };
    return SDL_PointInRectFloat(&fp, &col);
}
