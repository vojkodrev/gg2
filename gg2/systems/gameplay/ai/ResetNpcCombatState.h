#pragma once
#include "../../../structs/core/Context.h"
#include "ClearNpcAiTarget.h"
#include "../attacks/aggroTable/ResetAggroTable.h"
#include "../attacks/debuff/ResetDebuff.h"
#include <cstdint>

inline void resetNpcCombatState(Context &ctx, uint32_t n)
{
    clearNpcAiTarget(n, ctx);
    resetAggroTable(ctx.data.npc.aggroTable, n);
    resetDebuff(ctx.data.npc.concussiveShotDebuff, n);
    resetDebuff(ctx.data.npc.serpentStingDebuff, n);
}
