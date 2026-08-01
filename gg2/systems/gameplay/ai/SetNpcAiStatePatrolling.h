#pragma once
#include "../../../structs/core/Context.h"
#include "ResetNpcFollowPath.h"

inline void setNpcAiStatePatrolling(uint32_t n, Context &ctx)
{
    resetNpcFollowPath(ctx, n);
    ctx.data.npc.ai.state[n] = NPCAiState::Patrolling;
}
