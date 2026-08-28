#include "ProgressBarPositionSystem.h"
#include "SetProgressBarPositions.h"
#include <cstdint>

void progressBarPositionSystem(Context &ctx)
{
    setProgressBarPositions(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.base,
        ctx.data.player.statistics,
        0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setProgressBarPositions(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.base,
            ctx.data.npc.statistics,
            i);
    }
}
