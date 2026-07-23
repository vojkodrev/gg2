#pragma once
#include "Context.h"
#include "EntityType.h"
#include "IsNpcTargetVisible.h"
#include "NpcMonsterConstants.h"
#include <cstdint>

inline bool isMonsterRangedTargetVisible(
    Context &ctx,
    uint32_t n,
    EntityType targetType,
    int targetId,
    const SDL_FRect &targetCol)
{
    auto &npc = ctx.data.npc;
    if (npc.ai.targetVisibleTimer[n] <= 0.0f)
    {
        npc.ai.targetVisibleTimer[n] = NPC_TARGET_VISIBLE_CHECK_TIME;
        npc.ai.targetVisible[n] = isNpcTargetVisible(
            ctx,
            n,
            targetType,
            static_cast<uint32_t>(targetId),
            targetCol);
    }

    return npc.ai.targetVisible[n];
}
