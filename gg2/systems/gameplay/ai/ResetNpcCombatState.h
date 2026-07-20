#pragma once
#include "../../../structs/core/Context.h"
#include "ClearNpcAiTarget.h"
#include "../attacks/aggroTable/ResetAggroTable.h"
#include "../attacks/debuff/ResetDebuff.h"
#include <cstdint>

inline void resetNpcCombatState(Context &ctx, uint32_t n)
{
    clearNpcAiTarget(n, ctx);
    ctx.data.npc.ai.targetVisibleTimer[n] = 0.0f;
    ctx.data.npc.ai.targetVisible[n] = false;
    resetAggroTable(ctx.data.npc.aggroTable, n);
    resetDebuff(ctx.data.npc.concussiveShotDebuff, n);
    resetDebuff(ctx.data.npc.serpentStingDebuff, n);
}
