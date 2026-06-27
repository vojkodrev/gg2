#include "TogglePlayerAutoAttackSystem.h"

void togglePlayerAutoAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit1Released)
        return;

    auto &autoAttack = ctx.data.player.autoAttack;
    const int npcIndex = ctx.data.player.selectedNpc;
    if (!autoAttack.active && npcIndex == -1)
        return;

    autoAttack.active = !autoAttack.active;
}
