#include "HandleMonsterReturnToSpawn.h"
#include "HasReachedRect.h"
#include "../../../utils/rect/CenteredRect.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "SetNpcAiStateIdle.h"

void handleMonsterReturnToSpawn(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    SDL_FPoint spawnPt = { ai.spawn.x[n], ai.spawn.y[n] };
    SDL_FRect spawnCol = centeredRect(spawnPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
    followAStarPathTo(n, ctx, spawnCol);
    if (hasReachedRect(ctx, n, spawnCol))
        setNpcAiStateIdle(n, ctx);
}
