#include "TogglePlayerAutoAttackSystem.h"

void togglePlayerAutoAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit1Released)
        return;

    auto &autoAttack = ctx.data.player.autoAttack;
    const int npcIndex = ctx.data.player.selectedNpc;
    if (!autoAttack.active[0] && npcIndex == -1)
        return;

    autoAttack.active[0] = !autoAttack.active[0];
}
