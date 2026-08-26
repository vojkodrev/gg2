#include "ArcaneExplosionDebuffSystem.h"
#include "../debuff/RemoveDebuff.h"

void arcaneExplosionDebuffSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    auto &debuff = npc.arcaneExplosionDebuff;
    for (uint32_t npcIndex = 0; npcIndex < MAX_NPCS; npcIndex++)
    {
        if (!npc.active[npcIndex])
            continue;

        for (uint32_t debuffIndex = 0;
            debuffIndex < debuff.pool.count[npcIndex];
            debuffIndex++)
        {
            if (!debuff.pool.active[npcIndex][debuffIndex])
                continue;

            debuff.timer[npcIndex][debuffIndex] -= ctx.frame.dt;
            if (debuff.timer[npcIndex][debuffIndex] <= 0.0f)
                removeDebuff(
                    debuff,
                    npcIndex,
                    static_cast<int>(debuffIndex));
        }
    }
}
