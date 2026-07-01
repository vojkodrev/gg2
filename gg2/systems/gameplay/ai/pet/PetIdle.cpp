#include "PetIdle.h"
#include "DistToPlayer.h"
#include "SetNpcAiStatePursuePlayer.h"
#include "NpcPetConstants.h"

void petIdle(uint32_t n, Context &ctx)
{
    if (distToPlayer(ctx, n) > NPC_PET_FOLLOW_RADIUS)
        setNpcAiStatePursuePlayer(n, ctx);
}
