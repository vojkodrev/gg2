#pragma once
#include "Context.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/AttackConstants.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/ProjectileType.h"
#include "../projectile/CreateTargetedProjectileEffect.h"

inline bool tryExecuteConcussiveShot(
    Context &ctx,
    EntityType parentType,
    int parentId,
    EntityType targetType,
    int targetId)
{
    float *concussiveShotCooldownTimer;
    float *globalCooldownTimer;
    int *mana;
    bool *manaDirty;
    bool *showAmmo;
    if (parentType == EntityType::Player)
    {
        concussiveShotCooldownTimer =
            &ctx.data.player.concussiveShotCooldownTimer;
        globalCooldownTimer = &ctx.data.player.globalCooldownTimer;
        mana = &ctx.data.player.statistics.mana.mana[parentId];
        manaDirty = &ctx.data.player.statistics.mana.dirty[parentId];
        showAmmo = &ctx.data.player.equipment.weapon.showAmmo[parentId];
    }
    else if (parentType == EntityType::NPC)
    {
        concussiveShotCooldownTimer =
            &ctx.data.npc.concussiveShotCooldownTimer[parentId];
        globalCooldownTimer = &ctx.data.npc.globalCooldownTimer[parentId];
        mana = &ctx.data.npc.statistics.mana.mana[parentId];
        manaDirty = &ctx.data.npc.statistics.mana.dirty[parentId];
        showAmmo = &ctx.data.npc.equipment.weapon.showAmmo[parentId];
    }
    else
        return false;

    if (*concussiveShotCooldownTimer > 0.0f ||
        *globalCooldownTimer > 0.0f ||
        *mana < CONCUSSIVE_SHOT_MANA_COST)
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

    *mana -= CONCUSSIVE_SHOT_MANA_COST;
    *manaDirty = true;
    *concussiveShotCooldownTimer = CONCUSSIVE_SHOT_COOLDOWN_TIME;
    *globalCooldownTimer = GLOBAL_COOLDOWN_DELAY;
    *showAmmo = false;
    return true;
}
