#include "MonsterIdle.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStatePursuingTarget.h"
#include "SetNpcAiStatePatrolling.h"
#include "../../../structs/core/EntityType.h"
#include "../../../utils/collision/DistToEntity.h"

void monsterIdle(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;
    if (distToEntity(ctx, n, EntityType::Player, 0) < NPC_DETECT_RADIUS)
    {
        setNpcAiStatePursuingTarget(n, ctx, EntityType::Player, 0);
    }
    else if (ai.idleTimer[n] <= 0.0f)
    {
        setNpcAiStatePatrolling(n, ctx);
    }
}
