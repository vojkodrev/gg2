#pragma once
#include "Context.h"
#include "EntityColAABB.h"
#include "IsNpcColBlocked.h"
#include "spatialhash/SpatialHashQuery.h"
#include "../../../../structs/collision/SpatialHashQueryCandidates.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/rect/CenteredRect.h"
#include <shared_mutex>

inline bool isMonsterRetreatPointClear(
    Context &ctx,
    uint32_t npcIndex,
    const SDL_FPoint &point)
{
    const SDL_FRect currentCol = entityColAABB(ctx.data.npc.base, npcIndex);
    const SDL_FRect candidateCol =
        centeredRect(point, currentCol.w, currentCol.h);
    SpatialHashQueryCandidates candidates;
    int candidateCount;
    {
        std::shared_lock lock(ctx.collision.spatialHashMutex);
        candidateCount = spatialHashQuery(
            ctx.collision.spatialHash,
            0,
            candidateCol,
            candidates);
    }

    return !isNpcColBlocked(
        ctx,
        candidateCol,
        candidates,
        candidateCount,
        (int)npcIndex,
        INVALID_ID,
        true);
}
