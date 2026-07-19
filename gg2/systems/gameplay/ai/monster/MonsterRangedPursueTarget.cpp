#include "MonsterRangedPursueTarget.h"
#include "SetNpcAiStateIdle.h"

void monsterRangedPursueTarget(Context &ctx, uint32_t n)
{
    setNpcAiStateIdle(ctx, n);
}
