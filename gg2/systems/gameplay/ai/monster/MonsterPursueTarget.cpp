#include "MonsterPursueTarget.h"
#include "SetNpcAiStatePursuingTarget.h"

void monsterPursueTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    setNpcAiStatePursuingTarget(n, ctx, target.type[n], target.id[n]);
}
