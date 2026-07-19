#include "MonsterRangedAttack.h"
#include "SetNpcAiStateIdle.h"

void monsterRangedAttack(Context &ctx, uint32_t n)
{
    setNpcAiStateIdle(ctx, n);
}
