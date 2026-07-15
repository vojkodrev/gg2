#include "PlayerSerpentStingAttackSystem.h"
#include "CanPlayerRangedAttack.h"
#include "../../../structs/core/constants/AttackConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include "../../../structs/core/constants/SerpentStingConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/ProjectileType.h"
#include "../projectile/SpawnPlayerTargetedProjectileEffect.h"

void playerSerpentStingAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit2Released)
        return;
    if (ctx.data.player.globalCooldownTimer > 0.0f)
        return;
    if (!canPlayerRangedAttack(ctx))
        return;
    if (ctx.data.player.statistics.mana.mana[0] < SERPENT_STING_MANA_COST)
        return;

    const int npcIndex = ctx.data.player.selectedNpc;
    const SDL_FColor tint = {
        POISON_TINT_R,
        POISON_TINT_G,
        POISON_TINT_B,
        POISON_TINT_A
    };
    const int effectIndex = spawnPlayerTargetedProjectileEffect(
        ctx,
        ctx.data.player.equipment.ammo.base,
        ProjectileType::SerpentSting,
        npcIndex,
        tint);
    if (effectIndex == INVALID_ID)
        return;

    ctx.data.player.statistics.mana.mana[0] -= SERPENT_STING_MANA_COST;
    ctx.data.player.statistics.mana.dirty[0] = true;
    ctx.data.player.globalCooldownTimer = GLOBAL_COOLDOWN_DELAY;
    ctx.data.player.equipment.weapon.showAmmo[0] = false;
}
