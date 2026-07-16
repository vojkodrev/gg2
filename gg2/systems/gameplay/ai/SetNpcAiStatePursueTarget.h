#pragma once
#include "../../structs/core/Context.h"

inline void setNpcAiStatePursueTarget(Context &ctx, uint32_t n)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::PursueTarget;
}
