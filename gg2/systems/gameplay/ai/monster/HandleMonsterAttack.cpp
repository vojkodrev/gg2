#include "HandleMonsterAttack.h"
#include "DistToNpcSpawn.h"
#include "AreColBoxesNear.h"
#include "EntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateGoToSpawn.h"
#include "SetNpcAiStateGoToPlayer.h"

void handleMonsterAttack(uint32_t n, Context &ctx)
{
    if (distToNpcSpawn(ctx, n) > NPC_LEASH_RADIUS)
    {
        setNpcAiStateGoToSpawn(n, ctx);
        return;
    }
    SDL_FRect playerCol = entityColAABB(ctx.data.player.base, 0);
    if (!areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
        setNpcAiStateGoToPlayer(n, ctx);
}
