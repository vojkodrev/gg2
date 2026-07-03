#include "AutoAttackTimerSystem.h"

void autoAttackTimerSystem(Context &ctx)
{
    auto &attackTimer = ctx.data.player.autoAttack.attackTimer[0];
    if (attackTimer > 0.0f)
    {
        attackTimer -= ctx.frame.dt;
        if (attackTimer < 0.0f)
            attackTimer = 0.0f;
    }

    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;

        auto &npcAttackTimer = npc.autoAttack.attackTimer[i];
        if (npcAttackTimer <= 0.0f)
            continue;

        npcAttackTimer -= ctx.frame.dt;
        if (npcAttackTimer < 0.0f)
            npcAttackTimer = 0.0f;
    }
}
