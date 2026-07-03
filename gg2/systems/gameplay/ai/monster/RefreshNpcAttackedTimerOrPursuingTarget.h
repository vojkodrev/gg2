#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/npc/NPCAiState.h"
#include "RefreshNpcAttackedTimer.h"
#include "SetNpcAiStatePursuingTarget.h"

inline void refreshNpcAttackedTimerOrPursuingTarget(
    uint32_t n,
    Context &ctx,
    EntityType targetType,
    int targetId)
{
    const NPCAiState aiState = ctx.data.npc.ai.state[n];
    if (aiState == NPCAiState::Idle || aiState == NPCAiState::Patrolling)
    {
        setNpcAiStatePursuingTarget(n, ctx, targetType, targetId);
    }
    else
    {
        refreshNpcAttackedTimer(n, ctx);
    }
}
