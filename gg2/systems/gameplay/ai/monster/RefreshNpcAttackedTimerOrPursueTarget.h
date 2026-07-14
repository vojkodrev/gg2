#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/npc/NPCAiState.h"
#include "RefreshNpcAttackedTimer.h"
#include "../SetNpcAiStatePursueTarget.h"

inline void refreshNpcAttackedTimerOrPursueTarget(
    uint32_t n,
    Context &ctx,
    EntityType targetType,
    int targetId)
{
    const NPCAiState aiState = ctx.data.npc.ai.state[n];
    if (aiState == NPCAiState::Idle || aiState == NPCAiState::Patrolling)
    {
        setNpcAiStatePursueTarget(n, ctx, targetType, targetId, true);
    }
    else
    {
        refreshNpcAttackedTimer(n, ctx);
    }
}
