#include "MonsterMeleeAi.h"
#include "MonsterIdle.h"
#include "MonsterPatrol.h"
#include "MonsterMeleePursueTarget.h"
#include "MonsterMeleeAttack.h"
#include "MonsterReturnToSpawn.h"

void monsterMeleeAi(Context &ctx, uint32_t n)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:          monsterIdle(ctx, n);                break;
    case NPCAiState::Patrolling:    monsterPatrol(ctx, n);              break;
    case NPCAiState::PursueTarget:  monsterMeleePursueTarget(ctx, n);   break;
    case NPCAiState::Attack:        monsterMeleeAttack(ctx, n);          break;
    case NPCAiState::ReturnToSpawn: monsterReturnToSpawn(ctx, n);       break;
    default: break;
    }
}
