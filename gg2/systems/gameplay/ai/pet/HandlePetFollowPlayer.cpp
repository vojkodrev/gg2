#include "HandlePetFollowPlayer.h"
#include "EntityColAABB.h"
#include "AreColBoxesNear.h"
#include "SetNpcAiStateIdle.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"

void handlePetFollowPlayer(uint32_t n, Context &ctx)
{
    SDL_FRect playerCol = entityColAABB(ctx.data.player.base, 0);

    if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    followAStarPathTo(n, ctx, playerCol);
}
