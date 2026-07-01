#include "PlayerConcussiveShotAttackSystem.h"
#include "CanPlayerRangedAttack.h"
#include "../../../structs/core/constants/AttackConstants.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/ProjectileType.h"
#include "../projectile/SpawnPlayerTargetedProjectileEffect.h"

void playerConcussiveShotAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit3Released)
        return;
    if (ctx.data.player.globalCooldownTimer > 0.0f)
        return;
    if (!canPlayerRangedAttack(ctx))
        return;
    if (ctx.data.player.statistics.mana.mana[0] < CONCUSSIVE_SHOT_MANA_COST)
        return;

    const int npcIndex = ctx.data.player.selectedNpc;
    const SDL_FColor tint = {
        SLOWED_TINT_R,
        SLOWED_TINT_G,
        SLOWED_TINT_B,
        SLOWED_TINT_A
    };
    const int effectIndex = spawnPlayerTargetedProjectileEffect(
        ctx,
        ctx.data.player.equipment.ammo.base,
        ProjectileType::ConcussiveShot,
        npcIndex,
        tint);
    if (effectIndex == -1)
        return;

    ctx.data.player.statistics.mana.mana[0] -= CONCUSSIVE_SHOT_MANA_COST;
    ctx.data.player.statistics.mana.dirty[0] = true;
    ctx.data.player.globalCooldownTimer = GLOBAL_COOLDOWN_DELAY;
    ctx.data.player.equipment.weapon.showAmmo[0] = false;
}
