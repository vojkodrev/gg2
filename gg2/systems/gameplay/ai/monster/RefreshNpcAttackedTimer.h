#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"

inline void refreshNpcAttackedTimer(Context &ctx, uint32_t n)
{
    ctx.data.npc.ai.attackedTimer[n] = NPC_ATTACKED_TIME;
}
