#include "MonsterRangedAi.h"
#include "MonsterIdle.h"
#include "MonsterPatrol.h"
#include "MonsterRangedPursueTarget.h"
#include "MonsterRangedAttack.h"
#include "MonsterReturnToSpawn.h"

void monsterRangedAi(Context &ctx, uint32_t n)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:          monsterIdle(ctx, n);                  break;
    case NPCAiState::Patrolling:    monsterPatrol(ctx, n);                break;
    case NPCAiState::PursueTarget:  monsterRangedPursueTarget(ctx, n);    break;
    case NPCAiState::Attack:        monsterRangedAttack(ctx, n);           break;
    case NPCAiState::ReturnToSpawn: monsterReturnToSpawn(ctx, n);         break;
    default: break;
    }
}
