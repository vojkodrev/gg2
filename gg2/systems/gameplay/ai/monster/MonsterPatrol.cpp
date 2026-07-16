#include "MonsterPatrol.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "HasReachedRect.h"
#include "../../../utils/rect/CenteredRect.h"
#include "astar/FollowAStarPathTo.h"
#include "DetectTargetAndPursue.h"
#include "SetNpcAiStateIdle.h"

void monsterPatrol(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    if (detectTargetAndPursue(n, ctx))
        return;

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
        {
            setNpcAiStateIdle(ctx, n);
        }
    }
}
