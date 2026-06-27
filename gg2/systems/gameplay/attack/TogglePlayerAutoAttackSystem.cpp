#include "TogglePlayerAutoAttackSystem.h"
#include "../../../structs/core/constants/PlayerConstants.h"

void togglePlayerAutoAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit1Released)
        return;

    auto &autoAttack = ctx.data.player.autoAttack;
    autoAttack.active = !autoAttack.active;
    autoAttack.attackTimer = PLAYER_AUTO_ATTACK_DELAY;
}
