#include "BarFrameSystem.h"
#include "SetEntityBarFrames.h"
#include <cstdint>

void barFrameSystem(Context &ctx)
{
    setEntityBarFrames(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.statistics,
        0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setEntityBarFrames(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.statistics,
            i);
    }
}
