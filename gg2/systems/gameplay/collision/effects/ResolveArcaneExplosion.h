#pragma once
#include "Context.h"
#include "../../attacks/damage/ApplyAttackDamage.h"
#include "../../attacks/debuff/AddDebuff.h"
#include "../../../structs/core/constants/ArcaneExplosionConstants.h"
#include "../../../structs/entity/EntityType.h"
#include <cstdint>

inline void resolveArcaneExplosion(
    Context &ctx,
    uint32_t npcIndex,
    EntityType parentType,
    int parentId)
{
    auto &npc = ctx.data.npc;
    auto &debuff = npc.arcaneExplosionDebuff;
    for (uint32_t debuffIndex = 0;
        debuffIndex < debuff.pool.count[npcIndex];
        debuffIndex++)
    {
        if (debuff.pool.active[npcIndex][debuffIndex] &&
            debuff.entityType[npcIndex][debuffIndex] == parentType &&
            debuff.entityId[npcIndex][debuffIndex] == parentId)
            return;
    }

    addDebuff(
        debuff,
        npcIndex,
        parentType,
        parentId,
        ARCANE_EXPLOSION_DEBUFF_TIME);

    applyAttackDamage(
        ctx,
        EntityType::NPC,
        npcIndex,
        npc.statistics,
        npc.group,
        npc.base,
        ARCANE_EXPLOSION_DAMAGE,
        0);
}
