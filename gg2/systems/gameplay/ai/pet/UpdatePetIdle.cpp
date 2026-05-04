#include "UpdatePetIdle.h"
#include "DistToPlayer.h"
#include "SetNpcAiStateGoToPlayer.h"
#include "NpcPetConstants.h"

void updatePetIdle(uint32_t n, Context &ctx)
{
    if (distToPlayer(ctx, n) > NPC_PET_FOLLOW_RADIUS)
        setNpcAiStateGoToPlayer(n, ctx);
}
