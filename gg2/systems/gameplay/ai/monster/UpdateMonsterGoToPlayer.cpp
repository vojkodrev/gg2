#include "UpdateMonsterGoToPlayer.h"
#include "DistToSpawn.h"
#include "AreColBoxesNear.h"
#include "EntityBaseColAABB.h"
#include "NpcMonsterConstants.h"
#include "astar/UpdateAStarPath.h"
#include "SetNpcAiStateGoToSpawn.h"
#include "SetNpcAiStateAttack.h"

void updateMonsterGoToPlayer(uint32_t n, Context &ctx)
{
    if (distToSpawn(ctx, n) > NPC_LEASH_RADIUS)
    {
        setNpcAiStateGoToSpawn(n, ctx);
        return;
    }

    SDL_FRect playerCol = entityBaseColAABB(ctx.data.player.base, 0);

    if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    updateAStarPath(n, ctx, playerCol);
}
