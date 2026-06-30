#include "ShowHealthbarSystem.h"
#include <cstdint>

void showHealthbarSystem(Context &ctx)
{
    ctx.data.player.healthbar.show[0] =
        ctx.data.player.statistics.health.hp[0] < ctx.data.player.statistics.health.maxHp[0];

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        ctx.data.npc.healthbar.show[i] =
            ctx.data.npc.statistics.health.hp[i] < ctx.data.npc.statistics.health.maxHp[i];
    }
}
