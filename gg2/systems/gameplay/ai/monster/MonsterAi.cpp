#include "MonsterAi.h"
#include "MonsterIdle.h"
#include "MonsterPatrol.h"
#include "MonsterChasePlayer.h"
#include "MonsterAttack.h"
#include "MonsterReturnToSpawn.h"

void monsterAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:          monsterIdle(n, ctx);            break;
    case NPCAiState::Patrolling:    monsterPatrol(n, ctx);          break;
    case NPCAiState::ChasePlayer:   monsterChasePlayer(n, ctx);     break;
    case NPCAiState::Attack:        monsterAttack(n, ctx);          break;
    case NPCAiState::ReturnToSpawn: monsterReturnToSpawn(n, ctx);   break;
    }
}
