#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"

inline void refreshNpcAttackedTimer(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.attackedTimer[n] = NPC_ATTACKED_TIME;
}
