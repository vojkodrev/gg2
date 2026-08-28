#include "ProgressBarFrameSystem.h"
#include "SetCastBarFrame.h"
#include "SetHealthManaBarFrames.h"
#include <cstdint>

void progressBarFrameSystem(Context &ctx)
{
    setHealthManaBarFrames(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.statistics,
        0);
    setCastBarFrame(ctx.data.player.castbar, 0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setHealthManaBarFrames(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.statistics,
            i);
    }
}
