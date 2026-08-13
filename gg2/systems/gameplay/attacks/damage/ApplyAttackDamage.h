#pragma once
#include "CalculateAttackDamage.h"
#include "../../ui/text/CreateEntityTextEffect.h"
#include "../statistics/SetHpDamage.h"
#include "../../../structs/core/Context.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/groups/Group.h"
#include "../../../structs/entity/EntityBase.h"
#include "../../../structs/statistics/Statistics.h"
#include <string>

template<int N>
inline int applyAttackDamage(
    Context &ctx,
    EntityType targetType,
    uint32_t targetId,
    Statistics<N> &statistics,
    Group<N> &group,
    EntityBase<N> &entityBase,
    int baseDamage,
    int randomRange)
{
    const int attackDamage = calculateAttackDamage(baseDamage, randomRange);
    const int damage = setHpDamage(statistics, targetId, attackDamage);
    if (damage > 0)
        createEntityTextEffect(
            ctx,
            group.id[targetId],
            targetType,
            targetId,
            entityBase,
            std::to_string(damage));
    return damage;
}
