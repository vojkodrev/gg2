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
    ctx.data.npc.ai.targetTooClose[n] = false;
    ctx.data.npc.ai.retreating[n] = false;
    ctx.data.npc.ai.rangedRetreatPointCheckTimer[n] = 0.0f;
    resetAggroTable(ctx.data.npc.aggroTable, n);
    resetDebuff(ctx.data.npc.concussiveShotDebuff, n);
    resetDebuff(ctx.data.npc.frostNovaDebuff, n);
    resetDebuff(ctx.data.npc.serpentStingDebuff, n);
    resetDebuff(ctx.data.npc.arcaneExplosionDebuff, n);
}
