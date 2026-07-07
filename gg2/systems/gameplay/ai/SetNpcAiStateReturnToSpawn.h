#pragma once
#include "../../../structs/core/Context.h"
#include "ClearNpcAiTarget.h"

inline void setNpcAiStateReturnToSpawn(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::ReturnToSpawn;
    clearNpcAiTarget(n, ctx);
}
