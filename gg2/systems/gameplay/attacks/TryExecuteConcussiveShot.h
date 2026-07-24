#pragma once
#include "Context.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/AttackConstants.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/ProjectileType.h"
#include "../../../structs/equipment/Weapon.h"
#include "../../../structs/statistics/Mana.h"
#include "../projectile/CalculatePerpendicularProjectileOffset.h"
#include "../projectile/CreateTargetedProjectileEffect.h"

template<int N>
inline bool tryExecuteConcussiveShot(
    Context &ctx,
    EntityType parentType,
    int parentId,
    EntityType targetType,
    int targetId,
    float &concussiveShotCooldownTimer,
    float &globalCooldownTimer,
    Mana<N> &mana,
    Weapon<N> &weapon,
    float projectileOffsetDistance = 0.0f)
{
    if (concussiveShotCooldownTimer > 0.0f ||
        globalCooldownTimer > 0.0f ||
        mana.mana[parentId] < CONCUSSIVE_SHOT_MANA_COST)
        return false;

    const SDL_FColor tint = {
        SLOWED_TINT_R,
        SLOWED_TINT_G,
        SLOWED_TINT_B,
        SLOWED_TINT_A
    };
    const int effectIndex = createTargetedProjectileEffect(
        ctx,
        parentType,
        parentId,
        targetType,
        targetId,
        ProjectileType::ConcussiveShot,
        tint);
    if (effectIndex == INVALID_ID)
        return false;

    const SDL_FPoint projectileOffset =
        calculatePerpendicularProjectileOffset(
            ctx,
            weapon,
            parentId,
            targetType,
            targetId,
            projectileOffsetDistance);
    ctx.data.effect.base.position.x[effectIndex] += projectileOffset.x;
    ctx.data.effect.base.position.y[effectIndex] += projectileOffset.y;
    ctx.data.effect.base.position.dirty[effectIndex] = true;
    mana.mana[parentId] -= CONCUSSIVE_SHOT_MANA_COST;
    mana.dirty[parentId] = true;
    concussiveShotCooldownTimer = CONCUSSIVE_SHOT_COOLDOWN_TIME;
    globalCooldownTimer = GLOBAL_COOLDOWN_DELAY;
    weapon.showAmmo[parentId] = false;
    return true;
}
