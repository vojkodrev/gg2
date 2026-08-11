#pragma once
#include "Context.h"
#include "../../attacks/ApplyAttackDamage.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include <cstdint>

inline void resolveAutoAttackProjectile(
    Context &ctx,
    EntityType targetType,
    uint32_t targetId,
    EntityType parentType,
    int parentId)
{
    int damage;
    if (targetType == EntityType::Player)
        damage = applyAttackDamage(
            ctx,
            targetType,
            targetId,
            ctx.data.player.statistics,
            ctx.data.player.group,
            ctx.data.player.base,
            NPC_PROJECTILE_DAMAGE,
            NPC_PROJECTILE_DAMAGE_RANDOM_RANGE);
    else if (targetType == EntityType::NPC)
        damage = applyAttackDamage(
            ctx,
            targetType,
            targetId,
            ctx.data.npc.statistics,
            ctx.data.npc.group,
            ctx.data.npc.base,
            PLAYER_PROJECTILE_DAMAGE,
            PLAYER_PROJECTILE_DAMAGE_RANDOM_RANGE);
    else
        return;

    if (targetType == EntityType::NPC)
        addToAggroTableValue(
            ctx.data.npc.aggroTable,
            targetId,
            parentType,
            parentId,
            (float)damage);
}
