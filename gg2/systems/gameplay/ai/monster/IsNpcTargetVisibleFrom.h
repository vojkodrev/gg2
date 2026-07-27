#pragma once
#include "Context.h"
#include "ColIdType.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "EntityColCenterWorld.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "spatialhash/SpatialHashQuery.h"
#include "../../../../structs/collision/SpatialHashQueryCandidates.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "../../../../utils/rect/CenteredRect.h"
#include <algorithm>
#include <cmath>
#include <shared_mutex>

inline bool isNpcTargetVisibleFrom(
    Context &ctx,
    uint32_t n,
    const SDL_FRect &targetCol,
    const SDL_FPoint &npcColCenter)
{
    const auto &equipment = ctx.data.npc.equipment;
    if (equipment.weapon.type[n] != WeaponType::Ranged)
        return false;

    const SDL_FRect ammoAnchor = {
        equipment.weapon.ammoAnchor.offX[n][0],
        equipment.weapon.ammoAnchor.offY[n][0],
        equipment.weapon.ammoAnchor.w[n][0],
        equipment.weapon.ammoAnchor.h[n][0]
    };
    SDL_FPoint ammoAnchorCenter = entityColCenterWorld(
        ammoAnchor,
        equipment.weapon.base.position,
        n);
    const SDL_FPoint currentNpcColCenter =
        entityColCenter(entityColAABB(ctx.data.npc.base, n));
    ammoAnchorCenter.x += npcColCenter.x - currentNpcColCenter.x;
    ammoAnchorCenter.y += npcColCenter.y - currentNpcColCenter.y;
    const SDL_FPoint targetColCenter = entityColCenter(targetCol);
    const SDL_FRect ammoCol = entityColAABB(equipment.ammo.base, n);
    const float visibilityHalfWidth =
        (std::sqrt(ammoCol.w * ammoCol.w + ammoCol.h * ammoCol.h) +
            NPC_TARGET_VISIBLE_AMMO_BUFFER) * 0.5f;
    const SDL_FRect queryRect = {
        std::min(ammoAnchorCenter.x, targetColCenter.x) - visibilityHalfWidth,
        std::min(ammoAnchorCenter.y, targetColCenter.y) - visibilityHalfWidth,
        std::abs(targetColCenter.x - ammoAnchorCenter.x) + visibilityHalfWidth * 2.0f,
        std::abs(targetColCenter.y - ammoAnchorCenter.y) + visibilityHalfWidth * 2.0f
    };

    SpatialHashQueryCandidates candidates;
    int candidateCount;
    {
        std::shared_lock lock(ctx.collision.spatialHashMutex);
        candidateCount = spatialHashQuery(
            ctx.collision.spatialHash,
            0,
            queryRect,
            candidates);
    }
    for (int i = 0; i < candidateCount; i++)
    {
        const uint32_t candidate = candidates[i];
        if (colIdType(candidate) != ColType::Object)
            continue;

        const SDL_FRect obstacle = getEntityColAABB(ctx, candidate);
        // Expanding the obstacle by half the corridor width lets a line test
        // represent the ammo-sized visibility corridor intersecting the obstacle.
        const SDL_FRect bufferedObstacle = centeredRect(
            entityColCenter(obstacle),
            obstacle.w,
            obstacle.h,
            visibilityHalfWidth);
        float x1 = ammoAnchorCenter.x;
        float y1 = ammoAnchorCenter.y;
        float x2 = targetColCenter.x;
        float y2 = targetColCenter.y;
        if (SDL_GetRectAndLineIntersectionFloat(
                &bufferedObstacle,
                &x1,
                &y1,
                &x2,
                &y2))
            return false;
    }

    return true;
}
