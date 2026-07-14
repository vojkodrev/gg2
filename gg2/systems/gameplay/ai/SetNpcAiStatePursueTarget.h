#pragma once
#include "../../structs/core/Context.h"
#include "../../structs/core/EntityType.h"
#include "SetNpcAiTarget.h"
#include "monster/RefreshNpcAttackedTimer.h"

inline void setNpcAiStatePursueTarget(
    uint32_t n,
    Context &ctx,
    EntityType targetType,
    int targetId,
    bool refreshAttackedTimer)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    if (refreshAttackedTimer)
        refreshNpcAttackedTimer(n, ctx);
    setNpcAiTarget(n, ctx, targetType, targetId);
    ctx.data.npc.ai.state[n] = NPCAiState::PursueTarget;
}
