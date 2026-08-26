#pragma once
#include "Context.h"
#include "../../attacks/damage/ApplyAttackDamage.h"
#include "../../attacks/debuff/AddDebuff.h"
#include "../../attacks/debuff/RemoveDebuff.h"
#include "../../../structs/core/constants/FrostNovaConstants.h"
#include "../../../structs/entity/EntityType.h"
#include <cstdint>

inline void resolveFrostNova(
    Context &ctx,
    uint32_t npcIndex,
    EntityType parentType,
    int parentId)
{
    auto &npc = ctx.data.npc;
    auto &debuff = npc.frostNovaDebuff;
    for (uint32_t debuffIndex = 0;
        debuffIndex < debuff.pool.count[npcIndex];
        debuffIndex++)
    {
        if (!debuff.pool.active[npcIndex][debuffIndex])
            continue;

        if (debuff.entityType[npcIndex][debuffIndex] == parentType &&
            debuff.entityId[npcIndex][debuffIndex] == parentId)
            return;

        removeDebuff(debuff, npcIndex, static_cast<int>(debuffIndex));
    }

    addDebuff(
        debuff,
        npcIndex,
        parentType,
        parentId,
        FROST_NOVA_DEBUFF_TIME);

    applyAttackDamage(
        ctx,
        EntityType::NPC,
        npcIndex,
        npc.statistics,
        npc.group,
        npc.base,
        FROST_NOVA_DAMAGE,
        0);
}
