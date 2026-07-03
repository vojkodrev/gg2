#include "MonsterPursuingTarget.h"
#include "SetNpcAiStatePursueTarget.h"

void monsterPursuingTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    setNpcAiStatePursueTarget(n, ctx, target.type[n], target.id[n]);
}
