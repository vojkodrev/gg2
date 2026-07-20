#pragma once
#include "Context.h"
#include "ColIdMake.h"
#include "EntityColCenter.h"
#include "EntityType.h"
#include "GetEntityColAABB.h"
#include "SpatialHashConstants.h"
#include "spatialhash/SpatialHashQuery.h"
#include <algorithm>
#include <cmath>
#include <shared_mutex>

inline bool isNpcTargetVisible(
    Context &ctx,
    uint32_t n,
    EntityType targetType,
    uint32_t targetId,
    const SDL_FRect &targetCol)
{
    const SDL_FPoint npcCenter = entityColCenter(entityColAABB(ctx.data.npc.base, n));
    const SDL_FPoint targetCenter = entityColCenter(targetCol);
    const SDL_FRect queryRect = {
        std::min(npcCenter.x, targetCenter.x),
        std::min(npcCenter.y, targetCenter.y),
        std::abs(targetCenter.x - npcCenter.x),
        std::abs(targetCenter.y - npcCenter.y)
    };

    uint32_t candidates[SPATIAL_HASH_TABLE_SIZE];
    std::shared_lock lock(ctx.collision.spatialHashMutex);
    const int candidateCount = spatialHashQuery(
        ctx.collision.spatialHash,
        0,
        queryRect,
        candidates,
        SPATIAL_HASH_TABLE_SIZE);
    const uint32_t npcColId = colIdMake(ColType::NPC, n);
    const uint32_t targetColId = targetType == EntityType::Player
        ? colIdMake(ColType::Player, targetId)
        : colIdMake(ColType::NPC, targetId);

    for (int i = 0; i < candidateCount; i++)
    {
        const uint32_t candidate = candidates[i];
        if (candidate == npcColId || candidate == targetColId)
            continue;

        const SDL_FRect obstacle = getEntityColAABB(ctx, candidate);
        float x1 = npcCenter.x;
        float y1 = npcCenter.y;
        float x2 = targetCenter.x;
        float y2 = targetCenter.y;
        if (SDL_GetRectAndLineIntersectionFloat(&obstacle, &x1, &y1, &x2, &y2))
            return false;
    }

    return true;
}
