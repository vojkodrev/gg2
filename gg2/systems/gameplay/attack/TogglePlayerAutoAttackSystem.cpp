#include "TogglePlayerAutoAttackSystem.h"
#include "../../../structs/npc/NPCAiType.h"

void togglePlayerAutoAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit1Released)
        return;

    auto &autoAttack = ctx.data.player.autoAttack;
    const int npcIndex = ctx.data.player.selectedNpc;
    if (npcIndex != -1 && ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
    {
        autoAttack.active = false;
        return;
    }

    if (!autoAttack.active && npcIndex == -1)
        return;

    autoAttack.active = !autoAttack.active;
}
