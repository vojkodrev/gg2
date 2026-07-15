#include "MonsterReturnToSpawn.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "HasReachedRect.h"
#include "../../../utils/rect/CenteredRect.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "ClearNpcAiTarget.h"
#include "SetNpcAiStateIdle.h"
#include "../../attacks/aggroTable/ResetAggroTable.h"

void monsterReturnToSpawn(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;
    if (ai.target.type[n] != EntityType::None)
    {
        clearNpcAiTarget(n, ctx);
        resetAggroTable(ctx.data.npc.aggroTable, n);
    }

    SDL_FPoint spawnPt = { ai.spawn.x[n], ai.spawn.y[n] };
    SDL_FRect spawnCol = centeredRect(spawnPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
    followAStarPathTo(n, ctx, spawnCol, INVALID_ID);
    if (hasReachedRect(ctx, n, spawnCol))
        setNpcAiStateIdle(n, ctx);
}
