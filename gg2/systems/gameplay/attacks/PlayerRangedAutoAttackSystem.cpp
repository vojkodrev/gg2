#include "PlayerRangedAutoAttackSystem.h"
#include "CanPlayerRangedAttack.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/ProjectileType.h"
#include "../projectile/SpawnPlayerTargetedProjectileEffect.h"

void playerRangedAutoAttackSystem(Context &ctx)
{
    if (ctx.data.player.autoAttack.active[0] && ctx.data.player.autoAttack.attackTimer[0] == 0.0f)
    {
        if (!canPlayerRangedAttack(ctx))
            return;

        const int npcIndex = ctx.data.player.selectedNpc;
        const SDL_FColor tint = {
            CLEAR_TINT_R,
            CLEAR_TINT_G,
            CLEAR_TINT_B,
            CLEAR_TINT_A
        };
        const int effectIndex = spawnPlayerTargetedProjectileEffect(
            ctx,
            ctx.data.player.equipment.ammo.base,
            ProjectileType::AutoAttack,
            npcIndex,
            tint);
        if (effectIndex == -1)
            return;
        ctx.data.player.autoAttack.attackTimer[0] = PLAYER_AUTO_ATTACK_DELAY;
        ctx.data.player.equipment.weapon.showAmmo[0] = false;
    }
}
