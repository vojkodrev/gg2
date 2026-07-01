#include "MonsterIdle.h"
#include "DistToPlayer.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStatePursuePlayer.h"
#include "SetNpcAiStatePatrolling.h"

void monsterIdle(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;
    float dt = ctx.frame.dt;

    ai.idleTimer[n] -= dt;
    if (distToPlayer(ctx, n) < NPC_DETECT_RADIUS)
    {
        setNpcAiStatePursuePlayer(n, ctx);
    }
    else if (ai.idleTimer[n] <= 0.0f)
    {
        setNpcAiStatePatrolling(n, ctx);
    }
}
