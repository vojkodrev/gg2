#include "FrostNovaDebuffSystem.h"
#include "../debuff/RemoveDebuff.h"

void frostNovaDebuffSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    auto &debuff = npc.frostNovaDebuff;
    for (uint32_t npcIndex = 0; npcIndex < MAX_NPCS; npcIndex++)
    {
        if (!npc.active[npcIndex])
            continue;

        for (uint32_t slot = 0; slot < debuff.pool.count[npcIndex]; slot++)
        {
            if (!debuff.pool.active[npcIndex][slot])
                continue;

            debuff.timer[npcIndex][slot] -= ctx.frame.dt;
            if (debuff.timer[npcIndex][slot] <= 0.0f)
                removeDebuff(debuff, npcIndex, static_cast<int>(slot));
        }
    }
}
