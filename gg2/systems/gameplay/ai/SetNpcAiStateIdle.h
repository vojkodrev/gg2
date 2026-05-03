#pragma once
#include "../../../structs/core/Context.h"
#include "RandomIdleTimer.h"

inline void setNpcAiStateIdle(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.idleTimer[n] = randomIdleTimer();
    ctx.data.npc.ai.state[n] = NPCAiState::Idle;
}
