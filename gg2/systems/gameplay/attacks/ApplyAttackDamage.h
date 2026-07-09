#pragma once
#include "CalculateAttackDamage.h"
#include "../effects/CreateEntityTextEffect.h"
#include "../statistics/SetHpDamage.h"
#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include <string>

inline int applyAttackDamage(
    Context &ctx,
    EntityType targetType,
    uint32_t targetId,
    int baseDamage,
    int randomRange)
{
    const int attackDamage = calculateAttackDamage(baseDamage, randomRange);

    switch (targetType)
    {
    case EntityType::Player:
    {
        const int damage = setHpDamage(ctx.data.player.statistics, targetId, attackDamage);
        if (damage > 0)
            createEntityTextEffect(
                ctx,
                ctx.data.player.groupId,
                targetType,
                targetId,
                ctx.data.player.base,
                std::to_string(damage));
        return damage;
    }
    case EntityType::NPC:
    {
        const int damage = setHpDamage(ctx.data.npc.statistics, targetId, attackDamage);
        if (damage > 0)
            createEntityTextEffect(
                ctx,
                ctx.data.npc.groupId[targetId],
                targetType,
                targetId,
                ctx.data.npc.base,
                std::to_string(damage));
        return damage;
    }
    default:
        return 0;
    }
}
