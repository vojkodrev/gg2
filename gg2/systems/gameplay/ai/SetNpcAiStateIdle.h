#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "ClearNpcAiTarget.h"
#include "../../../utils/timers/RandomTimer.h"

inline void setNpcAiStateIdle(Context &ctx, uint32_t n)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
    ctx.data.npc.ai.state[n] = NPCAiState::Idle;
    clearNpcAiTarget(n, ctx);
}
