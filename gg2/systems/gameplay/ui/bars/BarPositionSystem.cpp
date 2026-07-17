#include "BarPositionSystem.h"
#include "SetEntityBarPositions.h"
#include <cstdint>

void barPositionSystem(Context &ctx)
{
    setEntityBarPositions(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.base,
        ctx.data.player.statistics,
        0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setEntityBarPositions(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.base,
            ctx.data.npc.statistics,
            i);
    }
}
