#include "SetHealthbarPositionSystem.h"
#include "SetHealthbarPosition.h"
#include <cstdint>

void setHealthbarPositionSystem(Context &ctx)
{
    if (ctx.data.player.base.position.dirty[0])
        setHealthbarPosition(ctx.data.player.healthbar.base, ctx.data.player.base, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (!ctx.data.npc.base.position.dirty[i])
            continue;

        setHealthbarPosition(ctx.data.npc.healthbar.base, ctx.data.npc.base, i);
    }
}
