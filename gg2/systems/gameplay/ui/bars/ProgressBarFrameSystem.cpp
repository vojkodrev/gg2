#include "ProgressBarFrameSystem.h"
#include "SetHealthManaBars.h"
#include <cstdint>

void progressBarFrameSystem(Context &ctx)
{
    setHealthManaBars(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.statistics,
        0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setHealthManaBars(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.statistics,
            i);
    }
}
