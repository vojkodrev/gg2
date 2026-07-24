#include "PlayerRangedAutoAttackSystem.h"
#include "CanPlayerRangedAttack.h"
#include "TryExecuteRangedAutoAttack.h"
#include "../../../structs/core/constants/PlayerConstants.h"

void playerRangedAutoAttackSystem(Context &ctx)
{
    if (ctx.data.player.autoAttack.active[0] && ctx.data.player.autoAttack.attackTimer[0] == 0.0f)
    {
        if (!canPlayerRangedAttack(ctx))
            return;

        tryExecuteRangedAutoAttack(
            ctx,
            EntityType::Player,
            0,
            EntityType::NPC,
            ctx.data.player.selectedNpc,
            ctx.data.player.autoAttack,
            ctx.data.player.equipment.weapon,
            PLAYER_AUTO_ATTACK_DELAY);
    }
}
