#include "PetPursueTarget.h"
#include "SetNpcAiStatePursuingTarget.h"
#include "SetNpcAiStateIdle.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"

void petPursueTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;

    if (target.type[n] != EntityType::NPC ||
        ctx.data.npc.ai.type[target.id[n]] != NPCAiType::Monster)
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    setNpcAiStatePursuingTarget(n, ctx, target.type[n], target.id[n]);
}
