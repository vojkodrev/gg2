#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../utils/npc/RandomTimer.h"

inline void setNpcAiStateIdle(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
    ctx.data.npc.ai.state[n] = NPCAiState::Idle;
}
