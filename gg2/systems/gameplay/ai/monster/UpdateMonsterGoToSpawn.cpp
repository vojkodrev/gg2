#include "UpdateMonsterGoToSpawn.h"
#include "HasReachedRect.h"
#include "CenteredRect.h"
#include "Constants.h"
#include "astar/UpdateAStarPath.h"
#include "SetNpcAiStateIdle.h"

void updateMonsterGoToSpawn(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    SDL_FPoint spawnPt = { ai.spawn.x[n], ai.spawn.y[n] };
    SDL_FRect spawnCol = centeredRect(spawnPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
    updateAStarPath(n, ctx, spawnCol);
    if (hasReachedRect(ctx, n, spawnCol))
        setNpcAiStateIdle(n, ctx);
}
