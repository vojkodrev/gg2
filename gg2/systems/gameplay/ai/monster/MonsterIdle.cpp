#include "MonsterIdle.h"
#include "DistToEntity.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStatePursueTarget.h"
#include "SetNpcAiStatePatrolling.h"
#include "../../../structs/core/EntityType.h"

void monsterIdle(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;
    float dt = ctx.frame.dt;

    ai.idleTimer[n] -= dt;
    if (distToEntity(ctx, n, EntityType::Player, 0) < NPC_DETECT_RADIUS)
    {
        setNpcAiStatePursueTarget(n, ctx, EntityType::Player, 0);
    }
    else if (ai.idleTimer[n] <= 0.0f)
    {
        setNpcAiStatePatrolling(n, ctx);
    }
}
