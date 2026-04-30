#include "UpdateMonsterIdle.h"
#include "DistToPlayer.h"
#include "Constants.h"
#include "SetNpcAiStateGoToPlayer.h"
#include "SetNpcAiStatePatrolling.h"

void updateMonsterIdle(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;
    float dt = ctx.frame.dt;

    ai.idleTimer[n] -= dt;
    if (distToPlayer(ctx, n) < NPC_DETECT_RADIUS)
    {
        setNpcAiStateGoToPlayer(n, ctx);
    }
    else if (ai.idleTimer[n] <= 0.0f)
    {
        setNpcAiStatePatrolling(n, ctx);
    }
}
