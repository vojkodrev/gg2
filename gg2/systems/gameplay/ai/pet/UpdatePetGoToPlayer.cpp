#include "UpdatePetGoToPlayer.h"
#include "EntityColAABBPlayer.h"
#include "AreColBoxesNear.h"
#include "SetNpcAiStateIdle.h"
#include "NpcMonsterConstants.h"
#include "astar/UpdateAStarPath.h"

void updatePetGoToPlayer(uint32_t n, Context &ctx)
{
    SDL_FRect playerCol = entityColAABB(ctx.data.player);

    if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    updateAStarPath(n, ctx, playerCol);
}
