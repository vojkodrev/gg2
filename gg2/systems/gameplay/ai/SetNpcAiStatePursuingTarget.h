#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include "SetNpcAiTarget.h"

inline void setNpcAiStatePursuingTarget(uint32_t n, Context &ctx, EntityType targetType, int targetId)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    setNpcAiTarget(n, ctx, targetType, targetId);
    ctx.data.npc.ai.state[n] = NPCAiState::PursuingTarget;
}
