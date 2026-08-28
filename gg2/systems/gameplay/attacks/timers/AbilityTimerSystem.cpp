#include "AbilityTimerSystem.h"
#include <algorithm>

void abilityTimerSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &castBar = ctx.data.player.castbar;
    castBar.previousTimer[0] = castBar.timer[0];
    castBar.timer[0] = std::max(0.0f, castBar.timer[0] - dt);

    auto &concussiveShotCooldownTimer = ctx.data.player.concussiveShotCooldownTimer;
    concussiveShotCooldownTimer =
        std::max(0.0f, concussiveShotCooldownTimer - dt);

    auto &frostNovaCooldownTimer = ctx.data.player.frostNovaCooldownTimer;
    frostNovaCooldownTimer = std::max(0.0f, frostNovaCooldownTimer - dt);

    for (uint32_t npcId = 0; npcId < MAX_NPCS; npcId++)
    {
        if (!ctx.data.npc.active[npcId])
            continue;

        auto &npcConcussiveShotCooldownTimer =
            ctx.data.npc.concussiveShotCooldownTimer[npcId];
        npcConcussiveShotCooldownTimer =
            std::max(0.0f, npcConcussiveShotCooldownTimer - dt);

        auto &tauntTimer = ctx.data.npc.tauntTimer[npcId];
        tauntTimer = std::max(0.0f, tauntTimer - dt);
    }
}
