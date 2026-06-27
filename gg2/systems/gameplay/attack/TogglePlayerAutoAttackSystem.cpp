#include "TogglePlayerAutoAttackSystem.h"

void togglePlayerAutoAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit1Released)
        return;

    auto &autoAttack = ctx.data.player.autoAttack;
    autoAttack.active = !autoAttack.active;
}
