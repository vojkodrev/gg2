#include "FollowNpcPatrolPath.h"
#include "HasReachedRect.h"
#include "SetNpcAiStateIdle.h"
#include "astar/FollowAStarPathTo.h"
#include "NpcMonsterConstants.h"
#include "IndexConstants.h"
#include "CenteredRect.h"

void followNpcPatrolPath(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    if (ai.patrol.count[n] == 0)
        return;

    uint32_t p = ai.patrol.index[n];
    SDL_FPoint patrolPt = { ai.spawn.x[n] + ai.patrol.point.x[n][p], ai.spawn.y[n] + ai.patrol.point.y[n][p] };
    SDL_FRect patrolCol = centeredRect(patrolPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
    followAStarPathTo(n, ctx, patrolCol, INVALID_ID);
    if (hasReachedRect(ctx, n, patrolCol))
    {
        ai.patrol.index[n] = (p + 1) % ai.patrol.count[n];
        if ((rand() % 100) + 1 <= 10)
            setNpcAiStateIdle(ctx, n);
    }
}
