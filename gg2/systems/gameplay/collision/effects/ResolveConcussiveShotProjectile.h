#pragma once
#include "Context.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../attacks/debuff/AddDebuff.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include <cstdint>

inline void resolveConcussiveShotProjectile(
    Context &ctx,
    uint32_t npcIndex,
    EntityType parentType,
    int parentId)
{
    addDebuff(
        ctx.data.npc.concussiveShotDebuff,
        npcIndex,
        parentType,
        parentId,
        CONCUSSIVE_SHOT_DEBUFF_TIME);

    addToAggroTableValue(
        ctx.data.npc.aggroTable,
        npcIndex,
        parentType,
        parentId,
        CONCUSSIVE_SHOT_AGGRO_VALUE);
}
