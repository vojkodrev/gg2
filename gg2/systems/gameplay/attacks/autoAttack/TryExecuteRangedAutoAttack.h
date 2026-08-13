#pragma once
#include "Context.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/ProjectileType.h"
#include "../../../structs/attacks/AutoAttack.h"
#include "../../../structs/equipment/Weapon.h"
#include "../projectile/CreateTargetedProjectileEffect.h"

template<int N>
inline bool tryExecuteRangedAutoAttack(
    Context &ctx,
    EntityType parentType,
    int parentId,
    EntityType targetType,
    int targetId,
    AutoAttack<N> &autoAttack,
    Weapon<N> &weapon,
    float attackDelay)
{
    const SDL_FColor tint = {
        CLEAR_TINT_R,
        CLEAR_TINT_G,
        CLEAR_TINT_B,
        CLEAR_TINT_A
    };
    const int effectIndex = createTargetedProjectileEffect(
        ctx,
        parentType,
        parentId,
        targetType,
        targetId,
        ProjectileType::AutoAttack,
        tint);
    if (effectIndex == INVALID_ID)
        return false;

    autoAttack.attackTimer[parentId] = attackDelay;
    weapon.ranged.showAmmo[parentId] = false;
    return true;
}
