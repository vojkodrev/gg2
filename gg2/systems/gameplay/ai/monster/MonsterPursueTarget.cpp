#include "MonsterPursueTarget.h"
#include "SetNpcAiStatePursuingTarget.h"

void monsterPursueTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];
    setNpcAiStatePursuingTarget(n, ctx, targetType, targetId);
}
