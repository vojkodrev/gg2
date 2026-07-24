#include "PlayerConcussiveShotAttackSystem.h"
#include "CanPlayerRangedAttack.h"
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
        ctx.data.player.selectedNpc);
}
