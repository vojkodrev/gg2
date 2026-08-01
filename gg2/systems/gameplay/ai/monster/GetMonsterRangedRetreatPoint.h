#pragma once
#include "Context.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "IsMonsterRetreatPointClear.h"
#include "../../attacks/IsRangedTargetVisible.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../utils/math/Dist.h"
#include <cmath>

inline SDL_FPoint getMonsterRangedRetreatPoint(
    Context &ctx,
    uint32_t n,
    const SDL_FRect &targetCol)
{
    const auto &ai = ctx.data.npc.ai;
    const SDL_FPoint monsterColCenter =
        entityColCenter(entityColAABB(ctx.data.npc.base, n));
    const SDL_FPoint targetColCenter = entityColCenter(targetCol);
    float awayX = monsterColCenter.x - targetColCenter.x;
    float awayY = monsterColCenter.y - targetColCenter.y;
    const float length = dist(
        monsterColCenter.x,
        monsterColCenter.y,
        targetColCenter.x,
        targetColCenter.y);

    if (length <= 0.001f)
    {
        awayX = 1.0f;
        awayY = 0.0f;
    }
    else
    {
        awayX /= length;
        awayY /= length;
    }

    const float retreatDistance =
        RANGED_ATTACK_MIN_DISTANCE +
        NPC_MONSTER_PATH_STEP +
        NPC_RANGED_RETREAT_EXTRA_DISTANCE;

    for (int i = 0; i < NPC_RANGED_RETREAT_ANGLE_COUNT; i++)
    {
        const float angle = NPC_RANGED_RETREAT_ANGLES[i];
        const float cosAngle = std::cos(angle);
        const float sinAngle = std::sin(angle);
        const SDL_FPoint direction = {
            awayX * cosAngle - awayY * sinAngle,
            awayX * sinAngle + awayY * cosAngle
        };
        const SDL_FPoint candidateColCenter = {
            targetColCenter.x + direction.x * retreatDistance,
            targetColCenter.y + direction.y * retreatDistance
        };

        if (isMonsterRetreatPointClear(ctx, n, candidateColCenter) &&
            isRangedTargetVisible(
                ctx,
                ctx.data.npc.equipment,
                ctx.data.npc.base,
                n,
                targetCol,
                candidateColCenter))
            return candidateColCenter;
    }

    return {ai.spawn.x[n], ai.spawn.y[n]};
}
