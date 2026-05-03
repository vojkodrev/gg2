#pragma once
#include "../../../structs/core/Context.h"

inline void setNpcAiStatePatrolling(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::Patrolling;
}
