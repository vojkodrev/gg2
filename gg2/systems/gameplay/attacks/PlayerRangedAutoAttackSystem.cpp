#include "PlayerRangedAutoAttackSystem.h"
#include "CanPlayerRangedAttack.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../projectile/SpawnPlayerTargetedProjectileEffect.h"

void playerRangedAutoAttackSystem(Context &ctx)
{
    if (ctx.data.player.autoAttack.active && ctx.data.player.autoAttack.attackTimer == 0.0f)
    {
        if (!canPlayerRangedAttack(ctx))
            return;

        const int npcIndex = ctx.data.player.selectedNpc;
        const int effectIndex = spawnPlayerTargetedProjectileEffect(
            ctx,
            ctx.data.player.equipment.ammo.base,
            npcIndex,
            CLEAR_TINT_R,
            CLEAR_TINT_G,
            CLEAR_TINT_B,
            CLEAR_TINT_A);
        if (effectIndex == -1)
            return;
        ctx.data.player.autoAttack.attackTimer = PLAYER_AUTO_ATTACK_DELAY;
        ctx.data.player.equipment.weapon.showAmmo[0] = false;
    }
}
