#include "MonsterReturnToSpawn.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "HasReachedRect.h"
#include "../../../utils/rect/CenteredRect.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "ResetNpcCombatState.h"
#include "SetNpcAiStateIdle.h"

void monsterReturnToSpawn(Context &ctx, uint32_t n)
{
    auto &ai = ctx.data.npc.ai;
    if (ai.target.type[n] != EntityType::None)
        resetNpcCombatState(ctx, n);

    SDL_FPoint spawnPt = { ai.spawn.x[n], ai.spawn.y[n] };
    SDL_FRect spawnCol = centeredRect(spawnPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
    followAStarPathTo(n, ctx, spawnCol, INVALID_ID);
    if (hasReachedRect(ctx, n, spawnCol))
        setNpcAiStateIdle(ctx, n);
}
