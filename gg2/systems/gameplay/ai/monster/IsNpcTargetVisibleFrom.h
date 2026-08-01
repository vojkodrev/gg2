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
    const SDL_FRect ammoCol = entityColAABB(equipment.ammo.base, n);
    const float visibilityHalfWidth =
        (std::sqrt(ammoCol.w * ammoCol.w + ammoCol.h * ammoCol.h) +
            NPC_TARGET_VISIBLE_AMMO_BUFFER) * 0.5f;
    const SDL_FPoint targetEdgePoint = {
        std::clamp(
            ammoAnchorCenter.x,
            targetCol.x,
            targetCol.x + targetCol.w),
        std::clamp(
            ammoAnchorCenter.y,
            targetCol.y,
            targetCol.y + targetCol.h)
    };
    const SDL_FRect queryRect = {
        std::min(ammoAnchorCenter.x, targetEdgePoint.x) - visibilityHalfWidth,
        std::min(ammoAnchorCenter.y, targetEdgePoint.y) - visibilityHalfWidth,
        std::abs(targetEdgePoint.x - ammoAnchorCenter.x) + visibilityHalfWidth * 2.0f,
        std::abs(targetEdgePoint.y - ammoAnchorCenter.y) + visibilityHalfWidth * 2.0f
    };
    const float lineDx = targetEdgePoint.x - ammoAnchorCenter.x;
    const float lineDy = targetEdgePoint.y - ammoAnchorCenter.y;
    const float lineLength = std::sqrt(lineDx * lineDx + lineDy * lineDy);
    if (lineLength <= 0.001f)
        return true;
    const float offsetX = -lineDy / lineLength * visibilityHalfWidth;
    const float offsetY = lineDx / lineLength * visibilityHalfWidth;

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
        float x1 = ammoAnchorCenter.x + offsetX;
        float y1 = ammoAnchorCenter.y + offsetY;
        float x2 = targetEdgePoint.x + offsetX;
        float y2 = targetEdgePoint.y + offsetY;
        if (SDL_GetRectAndLineIntersectionFloat(
                &obstacle,
                &x1,
                &y1,
                &x2,
                &y2))
            return false;

        x1 = ammoAnchorCenter.x - offsetX;
        y1 = ammoAnchorCenter.y - offsetY;
        x2 = targetEdgePoint.x - offsetX;
        y2 = targetEdgePoint.y - offsetY;
        if (SDL_GetRectAndLineIntersectionFloat(
                &obstacle,
                &x1,
                &y1,
                &x2,
                &y2))
            return false;
    }

    return true;
}
