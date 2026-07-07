#include "ConcussiveShotCooldownTimerSystem.h"

void concussiveShotCooldownTimerSystem(Context &ctx)
{
    auto &concussiveShotCooldownTimer = ctx.data.player.concussiveShotCooldownTimer;
    if (concussiveShotCooldownTimer > 0.0f)
    {
        concussiveShotCooldownTimer -= ctx.frame.dt;
        if (concussiveShotCooldownTimer < 0.0f)
            concussiveShotCooldownTimer = 0.0f;
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        auto &concussiveShotDebuffTimer = ctx.data.npc.concussiveShotDebuffTimer[i];
        if (concussiveShotDebuffTimer <= 0.0f)
            continue;

        concussiveShotDebuffTimer -= ctx.frame.dt;
        if (concussiveShotDebuffTimer < 0.0f)
            concussiveShotDebuffTimer = 0.0f;
    }
}
