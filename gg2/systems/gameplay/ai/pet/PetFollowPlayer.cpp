#include "PetFollowPlayer.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "EntityColAABB.h"
#include "AreColBoxesNear.h"
#include "SetNpcAiStateIdle.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"

void petFollowPlayer(uint32_t n, Context &ctx)
{
    SDL_FRect playerCol = entityColAABB(ctx.data.player.base, 0);

    if (areColBoxesNear(ctx, n, playerCol, NPC_MELEE_ATTACK_REACH))
    {
        setNpcAiStateIdle(ctx, n);
        return;
    }

    followAStarPathTo(n, ctx, playerCol, INVALID_ID);
}
