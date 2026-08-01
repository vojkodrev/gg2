#pragma once
#include "../../structs/core/Context.h"
#include "ResetNpcFollowPath.h"

inline void setNpcAiStatePursueTarget(Context &ctx, uint32_t n)
{
    resetNpcFollowPath(ctx, n);
    ctx.data.npc.ai.state[n] = NPCAiState::PursueTarget;
}
