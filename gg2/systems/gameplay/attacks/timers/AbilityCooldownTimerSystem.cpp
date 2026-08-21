#include "AbilityCooldownTimerSystem.h"

void abilityCooldownTimerSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &concussiveShotCooldownTimer = ctx.data.player.concussiveShotCooldownTimer;
    if (concussiveShotCooldownTimer > 0.0f)
    {
        concussiveShotCooldownTimer -= dt;
        if (concussiveShotCooldownTimer < 0.0f)
            concussiveShotCooldownTimer = 0.0f;
    }

    auto &frostNovaCooldownTimer = ctx.data.player.frostNovaCooldownTimer;
    if (frostNovaCooldownTimer > 0.0f)
    {
        frostNovaCooldownTimer -= dt;
        if (frostNovaCooldownTimer < 0.0f)
            frostNovaCooldownTimer = 0.0f;
    }

    for (uint32_t npcId = 0; npcId < MAX_NPCS; npcId++)
    {
        if (!ctx.data.npc.active[npcId])
            continue;

        auto &npcConcussiveShotCooldownTimer =
            ctx.data.npc.concussiveShotCooldownTimer[npcId];
        if (npcConcussiveShotCooldownTimer > 0.0f)
        {
            npcConcussiveShotCooldownTimer -= dt;
            if (npcConcussiveShotCooldownTimer < 0.0f)
                npcConcussiveShotCooldownTimer = 0.0f;
        }

        auto &tauntTimer = ctx.data.npc.tauntTimer[npcId];
        if (tauntTimer > 0.0f)
        {
            tauntTimer -= dt;
            if (tauntTimer < 0.0f)
                tauntTimer = 0.0f;
        }
    }
}
