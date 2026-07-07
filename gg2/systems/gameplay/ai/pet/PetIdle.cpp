#include "PetIdle.h"
#include "SetNpcAiTarget.h"
#include "SetNpcAiStateFollowPlayer.h"
#include "NpcPetConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../utils/collision/DistToEntity.h"

void petIdle(uint32_t n, Context &ctx)
{
    if (distToEntity(ctx, n, EntityType::Player, 0) > NPC_PET_FOLLOW_RADIUS)
        setNpcAiStateFollowPlayer(n, ctx);
}
