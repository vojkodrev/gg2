#pragma once
#include "Context.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../attacks/debuff/AddDebuff.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include <cstdint>

inline void resolveConcussiveShotProjectile(
    Context &ctx,
    EntityType targetType,
    uint32_t targetId,
    EntityType parentType,
    int parentId)
{
    if (targetType == EntityType::Player)
        addDebuff(
            ctx.data.player.concussiveShotDebuff,
            targetId,
            parentType,
            parentId,
            CONCUSSIVE_SHOT_DEBUFF_TIME);
    else if (targetType == EntityType::NPC)
    {
        addDebuff(
            ctx.data.npc.concussiveShotDebuff,
            targetId,
            parentType,
            parentId,
            CONCUSSIVE_SHOT_DEBUFF_TIME);

        addToAggroTableValue(
            ctx.data.npc.aggroTable,
            targetId,
            parentType,
            parentId,
            CONCUSSIVE_SHOT_AGGRO_VALUE);
    }
}
