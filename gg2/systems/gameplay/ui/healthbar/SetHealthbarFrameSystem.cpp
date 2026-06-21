#include "SetHealthbarFrameSystem.h"
#include "SetHealthbarFrame.h"
#include <cstdint>

void setHealthbarFrameSystem(Context &ctx)
{
    setHealthbarFrame(ctx.data.player.healthbar, ctx.data.player.statistics, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        setHealthbarFrame(ctx.data.npc.healthbar, ctx.data.npc.statistics, i);
}
