#pragma once
#include "../../../../../structs/ai/AStarContext.h"
#include "../../../../../utils/rect/CenteredRect.h"
#include "../node/AStarDecode.h"
#include <SDL3/SDL.h>

template<uint32_t N>
bool isGoalReached(
    const AStarContext<N>& astar,
    uint32_t astarIndex,
    const SDL_FRect& moverBox,
    const SDL_FPoint& moverCenter,
    const SDL_FRect& targetCol,
    int node)
{
    const SDL_Point p = astarDecode(astar, astarIndex, node);
    const SDL_FRect nodeMoverBox = centeredRect(
        { (float)p.x, (float)p.y },
        moverBox,
        moverCenter);
    return SDL_HasRectIntersectionFloat(&nodeMoverBox, &targetCol);
}
