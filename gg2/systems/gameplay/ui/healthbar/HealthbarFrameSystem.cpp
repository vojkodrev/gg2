#include "HealthbarFrameSystem.h"
#include "SetHealthbarFrame.h"
#include <cstdint>

void healthbarFrameSystem(Context &ctx)
{
    if (ctx.data.player.healthbar.show[0] && ctx.data.player.statistics.hpDirty[0])
        setHealthbarFrame(ctx.data.player.healthbar, ctx.data.player.statistics, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (ctx.data.npc.healthbar.show[i] && ctx.data.npc.statistics.hpDirty[i])
            setHealthbarFrame(ctx.data.npc.healthbar, ctx.data.npc.statistics, i);
    }
}
