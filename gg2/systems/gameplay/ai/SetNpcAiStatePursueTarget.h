#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"

inline void setNpcAiStatePursueTarget(uint32_t n, Context &ctx, EntityType targetType, int targetId)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.target.type[n] = targetType;
    ctx.data.npc.ai.target.id[n] = targetId;
    ctx.data.npc.ai.state[n] = NPCAiState::PursueTarget;
}
