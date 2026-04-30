#include "UpdateMonster.h"
#include "UpdateMonsterIdle.h"
#include "UpdateMonsterPatrolling.h"
#include "UpdateMonsterGoToPlayer.h"
#include "UpdateMonsterAttack.h"
#include "UpdateMonsterGoToSpawn.h"

void updateMonster(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:       updateMonsterIdle(n, ctx);        break;
    case NPCAiState::Patrolling: updateMonsterPatrolling(n, ctx);  break;
    case NPCAiState::GoToPlayer: updateMonsterGoToPlayer(n, ctx);  break;
    case NPCAiState::Attack:     updateMonsterAttack(n, ctx);      break;
    case NPCAiState::GoToSpawn:  updateMonsterGoToSpawn(n, ctx);   break;
    }
}
