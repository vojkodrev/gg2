#include "FriendlyIdle.h"
#include "SetNpcAiStatePatrolling.h"

void friendlyIdle(Context &ctx, uint32_t n)
{
    if (ctx.data.npc.ai.idleTimer[n] <= 0.0f)
        setNpcAiStatePatrolling(n, ctx);
}
