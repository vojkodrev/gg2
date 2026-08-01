#pragma once
#include "Context.h"
#include "EntityType.h"
#include "GetMonsterRangedRetreatPoint.h"
#include "IsMonsterRangedAttackTargetTooClose.h"
#include "IsMonsterRangedTargetVisible.h"
#include "../ResetNpcFollowPath.h"
#include "../astar/FollowAStarPathTo.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../utils/rect/CenteredRect.h"
#include <cstdint>

inline bool retreatRangedMonster(
    Context &ctx,
    uint32_t n,
    EntityType targetType,
    int targetId,
    const SDL_FRect &targetCol)
{
    auto &ai = ctx.data.npc.ai;
    const bool shouldRetreat =
        ai.retreating[n] ||
        isMonsterRangedAttackTargetTooClose(
            ctx,
            n,
            targetType,
            targetId);
    if (!shouldRetreat)
        return true;

    if (!ai.retreating[n] &&
        ai.rangedRetreatPointCheckTimer[n] <= 0.0f)
    {
        ai.rangedRetreatPointCheckTimer[n] =
            NPC_RANGED_RETREAT_POINT_CHECK_TIME;
        const SDL_FPoint retreatPoint =
            getMonsterRangedRetreatPoint(ctx, n, targetCol);
        ai.retreatPointX[n] = retreatPoint.x;
        ai.retreatPointY[n] = retreatPoint.y;
        ai.retreating[n] = true;
        resetNpcFollowPath(ctx, n);
    }

    const SDL_FRect retreatRect = centeredRect(
        {ai.retreatPointX[n], ai.retreatPointY[n]},
        NPC_PATROL_POINT_SIZE,
        NPC_PATROL_POINT_SIZE);
    const int targetNpcIndex =
        targetType == EntityType::NPC ? targetId : INVALID_ID;
    const bool goalReached =
        followAStarPathTo(n, ctx, retreatRect, targetNpcIndex);
    if (goalReached)
    {
        ai.retreating[n] = false;
        ai.rangedAttackTargetTooCloseCheckTimer[n] = 0.0f;
    }

    return isMonsterRangedTargetVisible(ctx, n, targetCol);
}
