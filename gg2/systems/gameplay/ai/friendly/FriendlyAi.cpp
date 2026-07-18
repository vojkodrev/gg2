#include "FriendlyAi.h"
#include "FriendlyIdle.h"
#include "FriendlyPatrol.h"

void friendlyAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:       friendlyIdle(n, ctx);   break;
    case NPCAiState::Patrolling: friendlyPatrol(n, ctx); break;
    default: break;
    }
}
