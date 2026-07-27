#pragma once
#include "../../../../../structs/ai/AStarContext.h"
#include "../../../../../structs/collision/SpatialHashQueryCandidates.h"
#include "../../../../../structs/core/Context.h"
#include "../../../../../utils/collision/EntityColAABB.h"
#include "../../../../../utils/collision/IsNpcColBlocked.h"
#include "../../../../../utils/collision/spatialhash/SpatialHashQuery.h"
#include "../../../../../utils/rect/CenteredRect.h"

template<uint32_t N>
bool isBlocked(
    const AStarContext<N>& astar, 
    uint32_t astarIndex, 
    const Context& ctx, 
    SDL_Point node, 
    int npcIndex,
    int targetNpcIndex)
{
    SDL_FRect npcCol = entityColAABB(ctx.data.npc.base, npcIndex);
    SDL_FRect moverBox = centeredRect({ (float)node.x, (float)node.y }, npcCol.w, npcCol.h);

    SpatialHashQueryCandidates candidates;
    int n = spatialHashQuery(
        astar.colHashSnapshot,
        astarIndex,
        moverBox,
        candidates);

    return isNpcColBlocked(
        ctx,
        moverBox,
        candidates,
        n,
        npcIndex,
        targetNpcIndex,
        false);
}
