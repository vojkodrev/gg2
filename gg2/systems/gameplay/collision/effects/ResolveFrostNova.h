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
    for (uint32_t slot = 0; slot < debuff.pool.count[npcIndex]; slot++)
    {
        if (debuff.pool.active[npcIndex][slot])
            removeDebuff(debuff, npcIndex, static_cast<int>(slot));
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
