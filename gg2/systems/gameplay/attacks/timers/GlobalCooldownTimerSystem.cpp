#include "GlobalCooldownTimerSystem.h"

void globalCooldownTimerSystem(Context &ctx)
{
    auto &globalCooldownTimer = ctx.data.player.globalCooldownTimer;
    if (globalCooldownTimer > 0.0f)
    {
        globalCooldownTimer -= ctx.frame.dt;
        if (globalCooldownTimer < 0.0f)
            globalCooldownTimer = 0.0f;
    }

    for (uint32_t npcId = 0; npcId < MAX_NPCS; npcId++)
    {
        if (!ctx.data.npc.active[npcId])
            continue;

        auto &npcGlobalCooldownTimer = ctx.data.npc.globalCooldownTimer[npcId];
        if (npcGlobalCooldownTimer > 0.0f)
        {
            npcGlobalCooldownTimer -= ctx.frame.dt;
            if (npcGlobalCooldownTimer < 0.0f)
                npcGlobalCooldownTimer = 0.0f;
        }
    }
}
