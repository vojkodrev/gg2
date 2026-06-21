#include "ShowHealthbarSystem.h"
#include <cstdint>

void showHealthbarSystem(Context &ctx)
{
    ctx.data.player.healthbar.show[0] =
        ctx.data.player.statistics.hp[0] < ctx.data.player.statistics.maxHp[0];

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        ctx.data.npc.healthbar.show[i] =
            ctx.data.npc.statistics.hp[i] < ctx.data.npc.statistics.maxHp[i];
}
