#include "SpawnNpcSystem.h"
#include "../../../structs/core/constants/NpcConstants.h"

void spawnNpcSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.initialized[i])
            continue;

        if (ctx.data.npc.active[i])
            continue;

        if (ctx.data.npc.inactiveTimer[i] > 0.0f)
        {
            ctx.data.npc.inactiveTimer[i] -= dt;
            if (ctx.data.npc.inactiveTimer[i] <= 0.0f)
                ctx.data.npc.inactiveTimer[i] = 0.0f;
        }
        else
        {
            ctx.data.npc.active[i] = true;
            ctx.data.npc.statistics.prevHp[i] = ctx.data.npc.statistics.maxHp[i];
            ctx.data.npc.statistics.hp[i] = ctx.data.npc.statistics.maxHp[i];
            ctx.data.npc.statistics.hpDirty[i] = true;
            ctx.data.npc.ai.patrol.index[i] = 0;
            ctx.data.npc.base.position.x[i] = ctx.data.npc.ai.spawn.x[i];
            ctx.data.npc.base.position.y[i] = ctx.data.npc.ai.spawn.y[i];
            ctx.data.npc.base.position.dirty[i] = true;
        }
    }
}
