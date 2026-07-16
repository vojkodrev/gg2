#pragma once
#include "Context.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../attacks/debuff/AddDebuff.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/SerpentStingConstants.h"
#include <cstdint>

inline void resolveSerpentStingProjectile(
    Context &ctx,
    uint32_t npcIndex,
    EntityType parentType,
    int parentId)
{
    addDebuff(
        ctx.data.npc.serpentStingDebuff,
        npcIndex,
        parentType,
        parentId,
        SERPENT_STING_DEBUFF_TIME);

    addToAggroTableValue(
        ctx.data.npc.aggroTable,
        npcIndex,
        parentType,
        parentId,
        0.0f);
}
