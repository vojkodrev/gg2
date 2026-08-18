#pragma once
#include "Context.h"
#include "MainEntityColAABB.h"
#include "EntityColCenter.h"
#include "../../attacks/ranged/IsRangedTargetVisible.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include <cstdint>

inline bool isMonsterRangedTargetVisible(
    Context &ctx,
    uint32_t n,
    const SDL_FRect &targetCol)
{
    auto &npc = ctx.data.npc;
    if (npc.ai.targetVisibleTimer[n] <= 0.0f)
    {
        npc.ai.targetVisibleTimer[n] = RANGED_TARGET_VISIBLE_CHECK_TIME;
        npc.ai.targetVisible[n] = isRangedTargetVisible(
            ctx,
            npc.equipment,
            npc.base,
            n,
            targetCol,
            entityColCenter(mainEntityColAABB(npc.base, n)));
    }

    return npc.ai.targetVisible[n];
}
