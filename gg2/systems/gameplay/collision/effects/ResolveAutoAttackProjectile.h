#pragma once
#include "Context.h"
#include "../../attacks/ApplyAttackDamage.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include <cstdint>

inline void resolveAutoAttackProjectile(
    Context &ctx,
    uint32_t npcIndex,
    EntityType parentType,
    int parentId)
{
    const int damage = applyAttackDamage(
        ctx,
        EntityType::NPC,
        npcIndex,
        ctx.data.npc.statistics,
        ctx.data.npc.group,
        ctx.data.npc.base,
        PROJECTILE_DAMAGE,
        PROJECTILE_DAMAGE_RANDOM_RANGE);

    addToAggroTableValue(
        ctx.data.npc.aggroTable,
        npcIndex,
        parentType,
        parentId,
        (float)damage);
}
