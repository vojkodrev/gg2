#include "PetPursueTarget.h"
#include "SetNpcAiStatePursuingTarget.h"
#include "SetNpcAiStateIdle.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"

void petPursueTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];

    if (targetType != EntityType::NPC ||
        ctx.data.npc.ai.type[targetId] != NPCAiType::Monster)
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    setNpcAiStatePursuingTarget(n, ctx, targetType, targetId);
}
