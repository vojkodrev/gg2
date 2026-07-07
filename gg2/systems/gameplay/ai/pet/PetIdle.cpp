#include "PetIdle.h"
#include "SetNpcAiTarget.h"
#include "SetNpcAiStatePursuingTarget.h"
#include "NpcPetConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../utils/collision/DistToEntity.h"

void petIdle(uint32_t n, Context &ctx)
{
    if (distToEntity(ctx, n, EntityType::Player, 0) > NPC_PET_FOLLOW_RADIUS)
        setNpcAiStatePursuingTarget(n, ctx, EntityType::Player, 0);
}
