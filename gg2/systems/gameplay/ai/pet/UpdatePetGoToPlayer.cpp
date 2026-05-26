#include "UpdatePetGoToPlayer.h"
#include "EntityBaseColAABB.h"
#include "AreColBoxesNear.h"
#include "SetNpcAiStateIdle.h"
#include "NpcMonsterConstants.h"
#include "astar/UpdateAStarPath.h"

void updatePetGoToPlayer(uint32_t n, Context &ctx)
{
    SDL_FRect playerCol = entityBaseColAABB(ctx.data.player.base, 0);

    if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    updateAStarPath(n, ctx, playerCol);
}
