#include "UpdateMonsterGoToPlayer.h"
#include "DistToSpawn.h"
#include "AreColBoxesNear.h"
#include "EntityColAABBPlayer.h"
#include "Constants.h"
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

    SDL_FRect playerCol = entityColAABB(ctx.data.player);

    if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    updateAStarPath(n, ctx, playerCol);
}
