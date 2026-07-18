#include "MonsterIdle.h"
#include "SetNpcAiStatePatrolling.h"
#include "DetectTargetAndPursue.h"

void monsterIdle(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;
    if (detectTargetAndPursue(ctx, n))
        return;

    if (ai.idleTimer[n] <= 0.0f)
    {
        setNpcAiStatePatrolling(n, ctx);
    }
}
