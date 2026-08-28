#include "ProgressBarVisibilitySystem.h"
#include "SetCastBarVisibility.h"
#include "SetHealthManaBarVisibility.h"
#include <cstdint>

void progressBarVisibilitySystem(Context &ctx)
{
    setHealthManaBarVisibility(
        ctx.data.player.healthbar,
        ctx.data.player.manabar,
        ctx.data.player.statistics,
        0);
    setCastBarVisibility(ctx.data.player.castbar, 0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setHealthManaBarVisibility(
            ctx.data.npc.healthbar,
            ctx.data.npc.manabar,
            ctx.data.npc.statistics,
            i);
    }
}
