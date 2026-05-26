#include "UpdateMonsterAttack.h"
#include "DistToSpawn.h"
#include "AreColBoxesNear.h"
#include "EntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateGoToSpawn.h"
#include "SetNpcAiStateGoToPlayer.h"

void updateMonsterAttack(uint32_t n, Context &ctx)
{
    if (distToSpawn(ctx, n) > NPC_LEASH_RADIUS)
    {
        setNpcAiStateGoToSpawn(n, ctx);
        return;
    }
    SDL_FRect playerCol = entityColAABB(ctx.data.player.base, 0);
    if (!areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
        setNpcAiStateGoToPlayer(n, ctx);
}
