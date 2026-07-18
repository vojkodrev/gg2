#include "FriendlyIdle.h"
#include "SetNpcAiStatePatrolling.h"

void friendlyIdle(uint32_t n, Context &ctx)
{
    if (ctx.data.npc.ai.idleTimer[n] <= 0.0f)
        setNpcAiStatePatrolling(n, ctx);
}
