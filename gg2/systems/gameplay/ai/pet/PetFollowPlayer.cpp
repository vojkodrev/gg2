#include "PetFollowPlayer.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "MainEntityColAABB.h"
#include "SetNpcAiStateIdle.h"
#include "astar/FollowAStarPathTo.h"

void petFollowPlayer(uint32_t n, Context &ctx)
{
    SDL_FRect playerCol = mainEntityColAABB(ctx.data.player.base, 0);

    const bool goalReached =
        followAStarPathTo(n, ctx, playerCol, INVALID_ID);
    if (goalReached)
        setNpcAiStateIdle(ctx, n);
}
