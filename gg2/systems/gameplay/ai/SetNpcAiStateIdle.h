#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "ResetNpcCombatState.h"
#include "ResetNpcFollowPath.h"
#include "../../../utils/timers/RandomTimer.h"

inline void setNpcAiStateIdle(Context &ctx, uint32_t n)
{
    resetNpcFollowPath(ctx, n);
    ctx.data.npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
    ctx.data.npc.ai.state[n] = NPCAiState::Idle;
    resetNpcCombatState(ctx, n);
}
