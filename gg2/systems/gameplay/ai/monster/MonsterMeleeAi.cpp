#include "MonsterMeleeAi.h"
#include "MonsterIdle.h"
#include "MonsterPatrol.h"
#include "MonsterMeleePursueTarget.h"
#include "MonsterMeleeAttack.h"
#include "MonsterReturnToSpawn.h"

void monsterMeleeAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:           monsterIdle(n, ctx);            break;
    case NPCAiState::Patrolling:     monsterPatrol(n, ctx);          break;
    case NPCAiState::PursueTarget:   monsterMeleePursueTarget(n, ctx); break;
    case NPCAiState::Attack:         monsterMeleeAttack(n, ctx);       break;
    case NPCAiState::ReturnToSpawn:  monsterReturnToSpawn(n, ctx);   break;
    default: break;
    }
}
