#include "PlayerConcussiveShotAttackSystem.h"
#include "../ranged/CanPlayerRangedAttack.h"
#include "TryExecuteConcussiveShot.h"

void playerConcussiveShotAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit3Released)
        return;
    if (!canPlayerRangedAttack(ctx))
        return;

    tryExecuteConcussiveShot(
        ctx,
        EntityType::Player,
        0,
        EntityType::NPC,
        ctx.data.player.selectedNpc,
        ctx.data.player.concussiveShotCooldownTimer,
        ctx.data.player.globalCooldownTimer,
        ctx.data.player.statistics.mana,
        ctx.data.player.equipment.weapon);
}
