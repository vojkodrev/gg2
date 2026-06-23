#include "DestroyNpcSystem.h"
#include "../../../structs/core/constants/NpcConstants.h"

void destroyNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (ctx.data.npc.statistics.hp[i] > 0)
            continue;

        ctx.data.npc.active[i] = false;
        ctx.data.npc.inactiveTimer[i] = NPC_INACTIVE_TIME;
    }
}
