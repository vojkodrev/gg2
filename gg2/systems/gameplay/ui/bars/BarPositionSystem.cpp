#include "BarPositionSystem.h"
#include "SetBarPosition.h"
#include "../../../structs/core/constants/HealthbarConstants.h"
#include <cstdint>

void barPositionSystem(Context &ctx)
{
    if (ctx.data.player.base.position.dirty[0] ||
        ctx.data.player.statistics.health.dirty[0] ||
        ctx.data.player.statistics.mana.dirty[0])
    {
        setBarPosition(ctx.data.player.healthbar.base, ctx.data.player.base, HEALTHBAR_Y_OFFSET, 0);
        setBarPosition(ctx.data.player.manabar.base, ctx.data.player.base, MANABAR_Y_OFFSET, 0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (!ctx.data.npc.base.position.dirty[i] && !ctx.data.npc.statistics.health.dirty[i])
            continue;

        setBarPosition(ctx.data.npc.healthbar.base, ctx.data.npc.base, 0.0f, i);
    }
}
