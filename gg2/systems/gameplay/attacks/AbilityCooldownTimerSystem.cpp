#include "AbilityCooldownTimerSystem.h"
#include "debuff/RemoveDebuff.h"

void abilityCooldownTimerSystem(Context &ctx)
{
    auto &concussiveShotCooldownTimer = ctx.data.player.concussiveShotCooldownTimer;
    if (concussiveShotCooldownTimer > 0.0f)
    {
        concussiveShotCooldownTimer -= ctx.frame.dt;
        if (concussiveShotCooldownTimer < 0.0f)
            concussiveShotCooldownTimer = 0.0f;
    }

    for (uint32_t npcId = 0; npcId < MAX_NPCS; npcId++)
    {
        if (!ctx.data.npc.active[npcId])
            continue;

        auto &growlTimer = ctx.data.npc.growlTimer[npcId];
        if (growlTimer > 0.0f)
        {
            growlTimer -= ctx.frame.dt;
            if (growlTimer < 0.0f)
                growlTimer = 0.0f;
        }

        auto &debuff = ctx.data.npc.concussiveShotDebuff;
        for (uint32_t debuffIndex = 0; debuffIndex < debuff.pool.count[npcId]; debuffIndex++)
        {
            if (!debuff.pool.active[npcId][debuffIndex])
                continue;

            debuff.timer[npcId][debuffIndex] -= ctx.frame.dt;
            if (debuff.timer[npcId][debuffIndex] <= 0.0f)
                removeDebuff(debuff, npcId, (int)debuffIndex);
        }
    }
}
