#pragma once
#include "../../../../../structs/ai/AStarContext.h"
#include "../../../../../structs/collision/SpatialHashQueryCandidates.h"
#include "../../../../../structs/core/Context.h"
#include "../../../../../utils/collision/IsNpcColBlocked.h"
#include "../../../../../utils/collision/spatialhash/SpatialHashQuery.h"
#include "../../../../../utils/rect/CenteredRect.h"

template<uint32_t N>
bool isBlocked(
    const AStarContext<N>& astar, 
    uint32_t astarIndex, 
    const Context& ctx, 
    SDL_Point node, 
    const SDL_FRect& moverBox,
    const SDL_FPoint& moverCenter,
    float moverBoxBuffer,
    int npcIndex,
    int targetNpcIndex,
    bool isPlayerBlocking)
{
    SDL_FRect nodeMoverBox = centeredRect(
        { (float)node.x, (float)node.y },
        moverBox,
        moverCenter,
        moverBoxBuffer);

    SpatialHashQueryCandidates candidates;
    int n = spatialHashQuery(
        astar.colHashSnapshot,
        astarIndex,
        nodeMoverBox,
        candidates);

    return isNpcColBlocked(
        ctx,
        nodeMoverBox,
        candidates,
        n,
        npcIndex,
        targetNpcIndex,
        isPlayerBlocking);
}
