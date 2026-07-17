#include "ShowBarSystem.h"
#include "SetEntityBarVisibility.h"
#include <cstdint>

void showBarSystem(Context &ctx)
{
    setEntityBarVisibility(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.statistics,
        0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setEntityBarVisibility(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.statistics,
            i);
    }
}
