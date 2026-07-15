#include "SpawnNpcSystem.h"
#include "../statistics/SetHp.h"
#include "../../../structs/core/constants/NpcConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../attacks/aggroTable/ResetAggroTable.h"
#include "../attacks/debuff/ResetDebuff.h"
#include "../ai/ClearNpcAiTarget.h"

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
            setHp(ctx.data.npc.statistics, i, ctx.data.npc.statistics.health.maxHp[i]);
            resetDebuff(ctx.data.npc.concussiveShotDebuff, i);
            resetDebuff(ctx.data.npc.serpentStingDebuff, i);
            ctx.data.npc.autoAttack.attackTimer[i] = 0.0f;
            ctx.data.npc.autoAttack.active[i] = false;
            resetAggroTable(ctx.data.npc.aggroTable, i);
            ctx.data.npc.ai.state[i] = NPCAiState::Idle;
            ctx.data.npc.ai.attackedTimer[i] = 0.0f;
            ctx.data.npc.ai.path.length[i] = 0;
            ctx.data.npc.ai.path.index[i] = 0;
            ctx.data.npc.ai.repathTimer[i] = 0.0f;
            ctx.data.npc.ai.patrol.index[i] = 0;
            clearNpcAiTarget(i, ctx);
            ctx.data.npc.base.tint.r[i] = CLEAR_TINT_R;
            ctx.data.npc.base.tint.g[i] = CLEAR_TINT_G;
            ctx.data.npc.base.tint.b[i] = CLEAR_TINT_B;
            ctx.data.npc.base.tint.a[i] = CLEAR_TINT_A;
            ctx.data.npc.base.tint.damageTimer[i] = 0.0f;
            ctx.data.npc.base.tint.isPoisoned[i] = false;
            ctx.data.npc.base.position.x[i] = ctx.data.npc.ai.spawn.x[i];
            ctx.data.npc.base.position.y[i] = ctx.data.npc.ai.spawn.y[i];
            ctx.data.npc.base.position.dirty[i] = true;
        }
    }
}
