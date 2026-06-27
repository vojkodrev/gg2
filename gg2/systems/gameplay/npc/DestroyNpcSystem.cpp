#include "DestroyNpcSystem.h"
#include "../../../structs/core/constants/NpcConstants.h"
#include "select/SetSelectedNpc.h"

void destroyNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (ctx.data.npc.statistics.hp[i] > 0)
            continue;

        if (ctx.data.player.selectedNpc == static_cast<int>(i))
        {
            setSelectedNpc(ctx, -1);
            ctx.data.player.autoAttack.active = false;
        }

        ctx.data.npc.active[i] = false;
        ctx.data.npc.inactiveTimer[i] = NPC_INACTIVE_TIME;
    }
}
