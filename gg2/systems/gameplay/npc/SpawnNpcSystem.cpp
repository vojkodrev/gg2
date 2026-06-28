#include "SpawnNpcSystem.h"
#include "../statistics/SetHp.h"
#include "../../../structs/core/constants/NpcConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../ai/SetNpcAiStateIdle.h"

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
            setHp(ctx.data.npc.statistics, i, ctx.data.npc.statistics.maxHp[i]);
            ctx.data.npc.serpentStingDebuff.debuffTimer[i] = 0.0f;
            setNpcAiStateIdle(i, ctx);
            ctx.data.npc.ai.path.length[i] = 0;
            ctx.data.npc.ai.path.index[i] = 0;
            ctx.data.npc.ai.repathTimer[i] = 0.0f;
            ctx.data.npc.ai.patrol.index[i] = 0;
            ctx.data.npc.base.tint.r[i] = CLEAR_TINT_R;
            ctx.data.npc.base.tint.g[i] = CLEAR_TINT_G;
            ctx.data.npc.base.tint.b[i] = CLEAR_TINT_B;
            ctx.data.npc.base.tint.a[i] = CLEAR_TINT_A;
            ctx.data.npc.base.tint.damageTimer[i] = 0.0f;
            ctx.data.npc.base.tint.poisonTimer[i] = 0.0f;
            ctx.data.npc.base.position.x[i] = ctx.data.npc.ai.spawn.x[i];
            ctx.data.npc.base.position.y[i] = ctx.data.npc.ai.spawn.y[i];
            ctx.data.npc.base.position.dirty[i] = true;
        }
    }
}
