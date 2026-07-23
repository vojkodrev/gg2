#pragma once
#include "Context.h"
#include "ColIdIndex.h"
#include "ColIdMake.h"
#include "ColIdType.h"
#include "EntityColCenter.h"
#include "EntityColCenterWorld.h"
#include "EntityType.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SpatialHashConstants.h"
#include "spatialhash/SpatialHashQuery.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "../../../../structs/npc/NPCAiType.h"
#include "../../../../utils/rect/CenteredRect.h"
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
    const auto &equipment = ctx.data.npc.equipment;
    if (
        equipment.weapon.type[n] != WeaponType::Ranged ||
        !equipment.weapon.showAmmo[n])
        return false;

    const SDL_FRect ammoAnchor = {
        equipment.weapon.ammoAnchor.offX[n][0],
        equipment.weapon.ammoAnchor.offY[n][0],
        equipment.weapon.ammoAnchor.w[n][0],
        equipment.weapon.ammoAnchor.h[n][0]
    };
    const SDL_FPoint ammoAnchorCenter = entityColCenterWorld(
        ammoAnchor,
        equipment.weapon.base.position,
        n);
    const SDL_FPoint targetCenter = entityColCenter(targetCol);
    const SDL_FRect ammoCol = entityColAABB(equipment.ammo.base, n);
    const float visibilityHalfWidth =
        (std::sqrt(ammoCol.w * ammoCol.w + ammoCol.h * ammoCol.h) +
            NPC_TARGET_VISIBLE_AMMO_BUFFER) * 0.5f;
    const SDL_FRect queryRect = {
        std::min(ammoAnchorCenter.x, targetCenter.x) - visibilityHalfWidth,
        std::min(ammoAnchorCenter.y, targetCenter.y) - visibilityHalfWidth,
        std::abs(targetCenter.x - ammoAnchorCenter.x) + visibilityHalfWidth * 2.0f,
        std::abs(targetCenter.y - ammoAnchorCenter.y) + visibilityHalfWidth * 2.0f
    };

    uint32_t candidates[SPATIAL_HASH_TABLE_SIZE];
    int candidateCount;
    {
        std::shared_lock lock(ctx.collision.spatialHashMutex);
        candidateCount = spatialHashQuery(
            ctx.collision.spatialHash,
            0,
            queryRect,
            candidates,
            SPATIAL_HASH_TABLE_SIZE);
    }
    const uint32_t npcColId = colIdMake(ColType::NPC, n);
    uint32_t targetColId;
    if (targetType == EntityType::Player)
        targetColId = colIdMake(ColType::Player, targetId);
    else if (targetType == EntityType::NPC)
        targetColId = colIdMake(ColType::NPC, targetId);
    else
        return false;

    const bool targetIsPlayer = targetType == EntityType::Player;
    const bool targetIsPet =
        targetType == EntityType::NPC &&
        ctx.data.npc.ai.type[targetId] == NPCAiType::Pet;

    for (int i = 0; i < candidateCount; i++)
    {
        const uint32_t candidate = candidates[i];
        if (candidate == npcColId || candidate == targetColId)
            continue;
        if (targetIsPlayer &&
            colIdType(candidate) == ColType::NPC &&
            ctx.data.npc.ai.type[colIdIndex(candidate)] == NPCAiType::Pet)
            continue;
        if (targetIsPet && colIdType(candidate) == ColType::Player)
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
        float x2 = targetCenter.x;
        float y2 = targetCenter.y;
        if (SDL_GetRectAndLineIntersectionFloat(&bufferedObstacle, &x1, &y1, &x2, &y2))
            return false;
    }

    return true;
}
