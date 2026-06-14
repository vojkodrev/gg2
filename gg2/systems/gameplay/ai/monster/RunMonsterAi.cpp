#include "RunMonsterAi.h"
#include "HandleMonsterIdle.h"
#include "HandleMonsterPatrol.h"
#include "HandleMonsterChasePlayer.h"
#include "HandleMonsterAttack.h"
#include "HandleMonsterReturnToSpawn.h"

void runMonsterAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:       handleMonsterIdle(n, ctx);        break;
    case NPCAiState::Patrolling: handleMonsterPatrol(n, ctx);  break;
    case NPCAiState::GoToPlayer: handleMonsterChasePlayer(n, ctx);  break;
    case NPCAiState::Attack:     handleMonsterAttack(n, ctx);      break;
    case NPCAiState::GoToSpawn:  handleMonsterReturnToSpawn(n, ctx);   break;
    }
}
