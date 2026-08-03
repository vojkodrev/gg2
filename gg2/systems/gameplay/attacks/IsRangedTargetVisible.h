#pragma once
#include "Context.h"
#include "ColIdType.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "EntityColCenterWorld.h"
#include "GetEntityColAABB.h"
#include "spatialhash/SpatialHashQuery.h"
#include "../../../structs/collision/SpatialHashQueryCandidates.h"
#include "../../../structs/core/constants/AttackConstants.h"
#include "../../../structs/equipment/Equipment.h"
#include "../../../structs/equipment/WeaponType.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <shared_mutex>

template<int N>
inline bool isRangedTargetVisible(
    Context &ctx,
    const Equipment<N> &equipment,
    const EntityBase<N> &entityBase,
    uint32_t entityIndex,
    const SDL_FRect &targetCol,
    const SDL_FPoint &entityColCenterFrom)
{
    if (equipment.weapon.type[entityIndex] != WeaponType::Ranged)
        return false;

    const int frameIndex =
        equipment.weapon.base.animation.frameIndex[entityIndex];
    const SDL_FRect ammoAnchor = {
        equipment.weapon.ranged.ammoAnchor.offX[entityIndex][frameIndex],
        equipment.weapon.ranged.ammoAnchor.offY[entityIndex][frameIndex],
        equipment.weapon.ranged.ammoAnchor.w[entityIndex][frameIndex],
        equipment.weapon.ranged.ammoAnchor.h[entityIndex][frameIndex]
    };
    SDL_FPoint ammoAnchorCenter = entityColCenterWorld(
        ammoAnchor,
        equipment.weapon.base.position,
        entityIndex);
    const SDL_FPoint currentEntityColCenter =
        entityColCenter(entityColAABB(entityBase, entityIndex));
    ammoAnchorCenter.x += entityColCenterFrom.x - currentEntityColCenter.x;
    ammoAnchorCenter.y += entityColCenterFrom.y - currentEntityColCenter.y;
    const SDL_FRect ammoCol =
        entityColAABB(equipment.ammo.base, entityIndex);
    const float visibilityHalfWidth =
        (std::sqrt(ammoCol.w * ammoCol.w + ammoCol.h * ammoCol.h) +
            RANGED_TARGET_VISIBLE_AMMO_BUFFER) * 0.5f;
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
        std::abs(targetEdgePoint.x - ammoAnchorCenter.x) +
            visibilityHalfWidth * 2.0f,
        std::abs(targetEdgePoint.y - ammoAnchorCenter.y) +
            visibilityHalfWidth * 2.0f
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
