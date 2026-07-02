#include "PetIdle.h"
#include "DistToEntity.h"
#include "SetNpcAiStatePursueTarget.h"
#include "NpcPetConstants.h"
#include "../../../structs/core/EntityType.h"

void petIdle(uint32_t n, Context &ctx)
{
    if (distToEntity(ctx, n, EntityType::Player, 0) > NPC_PET_FOLLOW_RADIUS)
        setNpcAiStatePursueTarget(n, ctx, EntityType::Player, 0);
}
