#pragma once
#include "Context.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/equipment/Weapon.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/collision/EntityColCenterWorld.h"
#include "../../../utils/collision/GetEntityColAABB.h"
#include <cmath>

template<int N>
inline SDL_FPoint calculatePerpendicularProjectileOffset(
    Context &ctx,
    const Weapon<N> &weapon,
    int parentId,
    EntityType targetType,
    int targetId,
    float distance)
{
    if (distance == 0.0f)
        return {0.0f, 0.0f};

    const int frameIndex = weapon.base.animation.frameIndex[parentId];
    const SDL_FRect ammoAnchor = {
        weapon.ranged.ammoAnchor.offX[parentId][frameIndex][0],
        weapon.ranged.ammoAnchor.offY[parentId][frameIndex][0],
        weapon.ranged.ammoAnchor.w[parentId][frameIndex][0],
        weapon.ranged.ammoAnchor.h[parentId][frameIndex][0]
    };
    const SDL_FPoint ammoAnchorCenter = entityColCenterWorld(
        ammoAnchor,
        weapon.base.position,
        parentId);
    const SDL_FPoint targetCenter =
        entityColCenter(getEntityColAABB(ctx, targetType, targetId));
    const float dx = targetCenter.x - ammoAnchorCenter.x;
    const float dy = targetCenter.y - ammoAnchorCenter.y;
    const float length = std::sqrt(dx * dx + dy * dy);
    if (length == 0.0f)
        return {0.0f, 0.0f};

    return {
        dy / length * distance,
        -dx / length * distance
    };
}
