#pragma once
#include "Context.h"
#include "EntityType.h"
#include "NpcMonsterConstants.h"
#include "../../attacks/IsRangedAttackTargetTooClose.h"
#include <cstdint>

inline bool isMonsterRangedAttackTargetTooClose(
    Context &ctx,
    uint32_t n,
    EntityType targetType,
    int targetId)
{
    auto &ai = ctx.data.npc.ai;
    if (ai.rangedAttackTargetTooCloseCheckTimer[n] <= 0.0f)
    {
        ai.rangedAttackTargetTooCloseCheckTimer[n] =
            NPC_RANGED_ATTACK_TARGET_TOO_CLOSE_CHECK_TIME;
        ai.targetTooClose[n] =
            isRangedAttackTargetTooClose(ctx, n, targetType, targetId);
    }

    return ai.targetTooClose[n];
}
