#include "FriendlyAi.h"
#include "FriendlyIdle.h"
#include "FriendlyPatrol.h"

void friendlyAi(Context &ctx, uint32_t n)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:       friendlyIdle(ctx, n);   break;
    case NPCAiState::Patrolling: friendlyPatrol(ctx, n); break;
    default: break;
    }
}
