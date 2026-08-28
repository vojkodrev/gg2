#include "ProgressBarDepthSystem.h"
#include <cstdint>

void progressBarDepthSystem(Context &ctx)
{
    ctx.data.player.healthbar.base.depthY[0] = ctx.data.player.base.depthY[0];
    ctx.data.player.manabar.base.depthY[0] = ctx.data.player.base.depthY[0];

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        ctx.data.npc.healthbar.base.depthY[i] = ctx.data.npc.base.depthY[i];
        ctx.data.npc.manabar.base.depthY[i] = ctx.data.npc.base.depthY[i];
    }
}
