#include "MonsterChasePlayer.h"
#include "DistToNpcSpawn.h"
#include "AreColBoxesNear.h"
#include "EntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "SetNpcAiStateGoToSpawn.h"
#include "SetNpcAiStateAttack.h"

void monsterChasePlayer(uint32_t n, Context &ctx)
{
    if (distToNpcSpawn(ctx, n) > NPC_LEASH_RADIUS)
    {
        setNpcAiStateGoToSpawn(n, ctx);
        return;
    }

    SDL_FRect playerCol = entityColAABB(ctx.data.player.base, 0);

    if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    followAStarPathTo(n, ctx, playerCol);
}
