#include "ConcussiveShotDebuffSystem.h"
#include "../debuff/RemoveDebuff.h"

void concussiveShotDebuffSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &playerDebuff = ctx.data.player.concussiveShotDebuff;
    for (uint32_t i = 0; i < playerDebuff.pool.count[0]; i++)
    {
        if (!playerDebuff.pool.active[0][i])
            continue;

        playerDebuff.timer[0][i] -= dt;
        if (playerDebuff.timer[0][i] <= 0.0f)
            removeDebuff(playerDebuff, 0, static_cast<int>(i));
    }

    auto &npc = ctx.data.npc;
    auto &npcDebuff = npc.concussiveShotDebuff;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;

        for (uint32_t j = 0; j < npcDebuff.pool.count[i]; j++)
        {
            if (!npcDebuff.pool.active[i][j])
                continue;

            npcDebuff.timer[i][j] -= dt;
            if (npcDebuff.timer[i][j] <= 0.0f)
                removeDebuff(npcDebuff, i, static_cast<int>(j));
        }
    }
}
